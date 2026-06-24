#pragma once
#include "ret_spoof.h"
#include <array>
class shadow_vmt
{
public:
	// Çalışan projeden alınan güvenli VMT hook metodu
	void VMT(void* Addr, void* PDes, int Index, void** Ret)
	{
		auto VTable = *static_cast<std::uintptr_t**>(Addr);
		int Methods = 0;

		do { ++Methods; }
		while (*reinterpret_cast<std::uintptr_t*>(
			reinterpret_cast<std::uintptr_t>(VTable) + (static_cast<unsigned long long>(Methods) * 0x8)));

		auto VTableBuf = new std::uint64_t[Methods * 0x8];

		for (auto Count = 0; Count < Methods; ++Count)
		{
			VTableBuf[Count] = *reinterpret_cast<std::uintptr_t*>(
				reinterpret_cast<std::uintptr_t>(VTable) + (static_cast<unsigned long long>(Count) * 0x8));
		}

		*Ret = reinterpret_cast<void*>(VTable[Index]);
		VTableBuf[Index] = reinterpret_cast<std::uintptr_t>(PDes);
		*reinterpret_cast<std::uint64_t**>(Addr) = VTableBuf;
	}

	template <typename type>
	bool hook(uint64_t module_base, uint64_t address, int index, void* function, type* original)
	{
		this->virtual_table = *(uintptr_t**)(address);
		if (reinterpret_cast<void*>(this->virtual_table[index]) != function)
		{
			while (this->virtual_table[this->vtable_size])
			{
				this->vtable_size++;
			}
			if (index < this->vtable_size)
			{
				this->allocated_vtable = reinterpret_cast<uintptr_t*>(
					fmemory::malloc(this->vtable_size * sizeof(uintptr_t), PAGE_EXECUTE_READWRITE)
					);

				for (int i = 0; i < this->vtable_size; i++)
				{
					this->allocated_vtable[i] = this->virtual_table[i];
				}
				*original = reinterpret_cast<type>(this->virtual_table[index]);
				this->allocated_vtable[index] = reinterpret_cast<uintptr_t>(function);
				*(uintptr_t**)(address) = this->allocated_vtable;
				return true;
			}
		}
		return false;
	}
private:

	uint64_t spoofed_malloc(int32_t size, uint32_t alignment)
	{
		return reinterpret_cast<uint64_t(__cdecl*)(int32_t, uint32_t, uintptr_t, void*)>(spoofcall_stub)(
			size,
			alignment,
			0x46C4660,
			(void*)&fmemory::malloc
			);
	}

	uintptr_t* virtual_table;
	uintptr_t* allocated_vtable;
	int vtable_size;
};





typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

extern "C" NTSTATUS __query_virtual_memory(
	HANDLE p_handle,
	void* base_addr,
	MEMORY_INFORMATION_CLASS memory_info_class,
	void* mbi,
	std::size_t mbi_length,
	std::size_t* mbi_out_length
);

namespace sheyko {
	class shadow {
	public:

		shadow() {}

		shadow(void* object) { this->initialize(object); }

		bool initialize(void* object, std::size_t size = 0) {
			this->object = object;
			if (this->object == nullptr) return false;

			this->object_vtable = *reinterpret_cast<std::uintptr_t**>(this->object);
			if (this->object_vtable == nullptr) return false;
			if (this->object_vtable == this->object_fake_vtable) return false;

			if (size == 0) {
				while (is_valid_ptr_value(this->object_vtable[size])) ++size;
				size *= sizeof(std::uintptr_t);
			}

			this->object_fake_vtable = reinterpret_cast<std::uintptr_t*>(VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
			if (this->object_fake_vtable == nullptr) return false;

			// Correction de __movsb - il prend 3 arguments
			unsigned char* dest = reinterpret_cast<unsigned char*>(this->object_fake_vtable);
			unsigned char* src = reinterpret_cast<unsigned char*>(this->object_vtable);
			__movsb(dest, src, size);

			*reinterpret_cast<std::uintptr_t**>(this->object) = this->object_fake_vtable;

			return true;
		}

		void restore_table() {
			if (this->object == nullptr) return;
			if (this->object_vtable == nullptr) return;
			*reinterpret_cast<std::uintptr_t**>(this->object) = this->object_vtable;
		}

		template <typename function>
		function apply(std::uintptr_t address, std::size_t index) {
			if (!address)
				return function();

			if (this->object_fake_vtable && index < get_vtable_size()) {
				std::uintptr_t original = this->object_fake_vtable[index];
				this->object_fake_vtable[index] = address;
				return reinterpret_cast<function>(original);
			}

			return function();
		}

		template<typename T>
		bool hook(uintptr_t module_base, uintptr_t object, std::size_t index, void* hook_function, T* original_function) {
			if (!initialize(reinterpret_cast<void*>(object))) {
				return false;
			}

			*original_function = apply<T>((std::uintptr_t)hook_function, index);
			return (*original_function != nullptr);
		}

		uint64_t get_address_from_index(std::size_t index) {
			if (this->object_fake_vtable && index < get_vtable_size()) {
				return this->object_fake_vtable[index];
			}
			return 0;
		}

	private:
		void* object = nullptr;
		std::uintptr_t* object_vtable = nullptr;
		std::uintptr_t* object_fake_vtable = nullptr;

		std::size_t get_vtable_size() {
			if (!object_vtable) return 0;
			std::size_t size = 0;
			while (is_valid_ptr_value(object_vtable[size])) ++size;
			return size;
		}

	public:
		static inline std::uintptr_t rwx_cave = std::uintptr_t();
		static inline std::int32_t total_function = std::int32_t();

		bool is_valid_ptr_value(std::uintptr_t pointer) {
			return pointer && (pointer >= 0x10000) && (pointer < 0xF000000000000);
		}

		static std::uintptr_t bind_function_to_rwx_cave(void* function) {
			if (shadow::rwx_cave == 0)
				return std::uintptr_t();

			// Utilisation correcte de std::array
			std::array<std::uint8_t, 15> stub = { 0xFF, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC3 };
			*reinterpret_cast<void**>(stub.data() + 6) = function;

			// Initialisation correcte de address
			std::uintptr_t address = (shadow::rwx_cave + 0x80) + (shadow::total_function * stub.size());

			// Correction de __movsb
			unsigned char* dest = reinterpret_cast<unsigned char*>(address);
			unsigned char* src = stub.data();
			__movsb(dest, src, stub.size());

			++shadow::total_function;

			return address;
		}

		static void unbind_all_functions()
		{
			if (shadow::total_function == 0 || shadow::rwx_cave == 0)
				return;

			std::array<std::uint8_t, 15> stub = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			for (int x = 0; x != shadow::total_function; x++)
			{
				// Initialisation correcte de address
				std::uintptr_t address = (shadow::rwx_cave + 0x80) + (x * stub.size());

				// Correction de __movsb
				unsigned char* dest = reinterpret_cast<unsigned char*>(address);
				unsigned char* src = stub.data();
				__movsb(dest, src, stub.size());
			}
		}

		static std::uintptr_t find_whitelisted_rwx_cave() {
			MEMORY_BASIC_INFORMATION mbi = {};
			std::uintptr_t address = std::uintptr_t();

			while (__query_virtual_memory(HANDLE(-1), reinterpret_cast<void*>(address), MemoryBasicInformation, &mbi, sizeof(mbi), nullptr) == 0) {
				if (address && mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.AllocationProtect == PAGE_EXECUTE_READWRITE && mbi.Type == MEM_PRIVATE && mbi.State == MEM_COMMIT) {
					std::uint8_t* pattern_address = reinterpret_cast<std::uint8_t*>(address);

					bool is_empty_end = true;
					for (std::size_t index = 100; index < mbi.RegionSize; index++) {
						if (!(pattern_address[index] == 0)) {
							if (is_empty_end) {
								is_empty_end = false;
							}
							else {
								break;
							}
						}
					}

					if (is_empty_end && pattern_address[0] == 0x48 && pattern_address[1] == 0x89 && pattern_address[2] == 0x5C && pattern_address[3] == 0x24)
						return address;
				}

				address += mbi.RegionSize;
			}

			return address;
		}
	};
}