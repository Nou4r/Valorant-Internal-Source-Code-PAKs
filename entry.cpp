#include "hooks.hpp"
#include "pak_mounter.hpp"
#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <process.h>
#include <cstdint>
#include <string>


__int64 get_fpak_platform_file()
{
    // fpak_platform_file = 0xC2E7278 (updated)
    uintptr_t base = (uintptr_t)GetModuleHandleA(nullptr);
    if (!base) return 0;
    
    uintptr_t delegate_ptr = base + offsets::get_fpak_platform_file;
    if (!memory::IsValidPointer(delegate_ptr)) return 0;
    
    auto delegate = *(__int64*)delegate_ptr;
    if (!delegate || !memory::IsValidPointer(delegate)) return 0;
    
    uintptr_t result_ptr = delegate + 24;
    if (!memory::IsValidPointer(result_ptr)) return 0;
    
    return *(__int64*)result_ptr;
}

void bypass_pak_signing()
{
    // bypass_pak_signing = 0xC643038 (updated)
    auto delegate = (uint8_t*)((uintptr_t)GetModuleHandleA(nullptr) + offsets::bypass_pak_signing);
    DWORD old_protect;
    if (VirtualProtect(delegate, 0x20, PAGE_READWRITE, &old_protect)) {
        memset(delegate, 0, 0x20);
        VirtualProtect(delegate, 0x20, old_protect, &old_protect);
    }

    auto fpak = get_fpak_platform_file();
    if (fpak) {
        auto bsigned_ptr = (uint8_t*)(fpak + 48);
        if (VirtualProtect(bsigned_ptr, 1, PAGE_READWRITE, &old_protect)) {
            *bsigned_ptr = 0;
            VirtualProtect(bsigned_ptr, 1, old_protect, &old_protect);
        }
    }
}

void mount_custom_pak(const wchar_t* path, int priority)
{
    auto fpak = get_fpak_platform_file();
    if (!fpak) return;

    // Check if file exists before mounting
    DWORD attrib = GetFileAttributesW(path);
    if (attrib == INVALID_FILE_ATTRIBUTES || (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return;
    }

    // mount = 0x28D2AD0 (updated)
    typedef bool(__fastcall* fn_mount)(__int64, const wchar_t*, int, const wchar_t*, bool, bool);
    auto mount = (fn_mount)((uintptr_t)GetModuleHandleA(nullptr) + offsets::mount);
    if (mount) {
        __try {
            mount(fpak, path, priority, nullptr, true, false);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // Silently fail if mount crashes
        }
    }
}
// ============================================================

typedef struct _MY_UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} MY_UNICODE_STRING, * PMY_UNICODE_STRING;

typedef struct _MY_LIST_ENTRY {
    struct _MY_LIST_ENTRY* Flink;
    struct _MY_LIST_ENTRY* Blink;
} MY_LIST_ENTRY, * PMY_LIST_ENTRY;

typedef struct _MY_LDR_DATA_TABLE_ENTRY {
    MY_LIST_ENTRY InLoadOrderLinks;
    MY_LIST_ENTRY InMemoryOrderLinks;
    MY_LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    MY_UNICODE_STRING FullDllName;
    MY_UNICODE_STRING BaseDllName;
} MY_LDR_DATA_TABLE_ENTRY, * PMY_LDR_DATA_TABLE_ENTRY;

typedef struct _MY_PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    PVOID SsHandle;
    MY_LIST_ENTRY InLoadOrderModuleList;
    MY_LIST_ENTRY InMemoryOrderModuleList;
    MY_LIST_ENTRY InInitializationOrderModuleList;
} MY_PEB_LDR_DATA, * PMY_PEB_LDR_DATA;

typedef struct _MY_PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN SpareBool;
    PVOID Mutant;
    PVOID ImageBaseAddress;
    PMY_PEB_LDR_DATA Ldr;
} MY_PEB, * PMY_PEB;

#ifndef CONTAINING_RECORD
#define CONTAINING_RECORD(address, type, field) \
    ((type *)((char*)(address) - (uintptr_t)(&((type *)0)->field)))
#endif

static void ClearPEHeaders(HMODULE hModule) {
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hModule;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((BYTE*)pDosHeader + pDosHeader->e_lfanew);
    SIZE_T headerSize = pNtHeaders->OptionalHeader.SizeOfHeaders;
    DWORD oldProtect;
    VirtualProtect((LPVOID)hModule, headerSize, PAGE_READWRITE, &oldProtect);
    ZeroMemory((LPVOID)hModule, headerSize);
    VirtualProtect((LPVOID)hModule, headerSize, oldProtect, &oldProtect);
}

static void UnlinkFromPEB(HMODULE hModule) {
    PMY_PEB pPEB = (PMY_PEB)__readgsqword(0x60);
    PMY_LIST_ENTRY pListEntry = pPEB->Ldr->InMemoryOrderModuleList.Flink;

    while (pListEntry != &pPEB->Ldr->InMemoryOrderModuleList) {
        PMY_LDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pListEntry, MY_LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (pEntry->DllBase == hModule) {
            pEntry->InLoadOrderLinks.Flink->Blink = pEntry->InLoadOrderLinks.Blink;
            pEntry->InLoadOrderLinks.Blink->Flink = pEntry->InLoadOrderLinks.Flink;
            pEntry->InMemoryOrderLinks.Flink->Blink = pEntry->InMemoryOrderLinks.Blink;
            pEntry->InMemoryOrderLinks.Blink->Flink = pEntry->InMemoryOrderLinks.Flink;
            pEntry->InInitializationOrderLinks.Flink->Blink = pEntry->InInitializationOrderLinks.Blink;
            pEntry->InInitializationOrderLinks.Blink->Flink = pEntry->InInitializationOrderLinks.Flink;
            RtlZeroMemory(&pEntry->BaseDllName, sizeof(MY_UNICODE_STRING));
            RtlZeroMemory(&pEntry->FullDllName, sizeof(MY_UNICODE_STRING));
            pEntry->SizeOfImage = 0;
            break;
        }
        pListEntry = pListEntry->Flink;
    }
}

extern "C" __declspec(dllexport) int windowsaudiocore85(int code, WPARAM wParam, LPARAM lParam) {
    return CallNextHookEx(NULL, code, wParam, lParam);
}

__declspec(safebuffers) static void WINAPI DllAttach([[maybe_unused]] LPVOID lp) noexcept {
    HMODULE hMod = (HMODULE)lp;

    using FnNtSIT = NTSTATUS(NTAPI*)(HANDLE, UINT, PVOID, ULONG);
    auto NtSIT = reinterpret_cast<FnNtSIT>(
        GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtSetInformationThread"));
    if (NtSIT) NtSIT(GetCurrentThread(), 0x11u, nullptr, 0u);

    memory::module_base = (uintptr_t)GetModuleHandleA(nullptr);
    if (!memory::module_base) return;


    initialize_spoofcall((uint8_t*)memory::module_base);

    ClearPEHeaders(hMod);
    UnlinkFromPEB(hMod);

    __try {
        for (int attempt = 0; attempt < 300; attempt++) {
            if (hooks::init_hooks())
                break;
            Sleep(100);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        // Hook initialization failed - return silently to prevent crash
        return;
    }
}

__declspec(safebuffers)BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, [[maybe_unused]] LPVOID reserved) {
    if (reason != DLL_PROCESS_ATTACH)
        return TRUE;

    // ---------- CUSTOM PAK MOUNT ----------
    bypass_pak_signing();
    mount_custom_pak(L"C:\\mods\\pakchunk1-Windows_P.pak", 10000);
    mount_custom_pak(L"C:\\mods\\pakchunk2-Windows_P.pak", 10001);
    mount_custom_pak(L"C:\\mods\\pakchunk3-Windows_P.pak", 10002);
    // ---------------------------------------------------------

    DisableThreadLibraryCalls(hModule);

    auto hThread = reinterpret_cast<HANDLE>(
        ::_beginthreadex(nullptr, 0u,
            reinterpret_cast<_beginthreadex_proc_type>(DllAttach),
            (LPVOID)hModule, 0u, nullptr));

    if (hThread)
        CloseHandle(hThread);

    return TRUE;
}