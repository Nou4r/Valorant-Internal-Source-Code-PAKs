#pragma once
#include <windows.h>
#include <cstdint>

#include "definitions.hpp"

#define null NULL
#define class_ptr uintptr_t(this)



namespace memory
{
    inline uintptr_t module_base = null;

    inline bool is_bad_write_ptr(LPVOID ptr, uint64_t size)
    {
        return ptr ? false : true;
    }

    inline bool valid_pointer(uint64_t address)
    {
        if (!is_bad_write_ptr((LPVOID)address, (uint64_t)8)) return true;
        else return false;
    }

    // ⭐ NOUVELLE FONCTION: Version plus robuste pour validation des pointeurs
    inline bool is_valid_ptr(uintptr_t ptr) {
        // Vérifications de base
        if (!ptr || ptr < 0x10000 || ptr > 0x7FFFFFFFFFFF) {
            return false;
        }

        // Vérification avec votre fonction existante
        if (!valid_pointer(ptr)) {
            return false;
        }

        // Test de lecture sécurisé avec SEH (Structured Exception Handling)
        __try {
            volatile auto test = *(char*)ptr;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline bool IsValidPointer(uintptr_t address, bool requireWrite = false) {
        MEMORY_BASIC_INFORMATION mbi;
        if (!VirtualQuery(reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi))) {
            return false;
        }
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) {
            return false;
        }
        if (requireWrite) {
            // List of writable page protections (for usermode)
            if (!(mbi.Protect & PAGE_READWRITE) &&
                !(mbi.Protect & PAGE_WRITECOPY) &&
                !(mbi.Protect & PAGE_EXECUTE_READWRITE) &&
                !(mbi.Protect & PAGE_EXECUTE_WRITECOPY)) {
                return false;
            }
        }
        return true;
    }

    // ⭐ FONCTION BONUS: Validation spécifique pour les objets du jeu
    inline bool is_valid_game_object(uintptr_t ptr) {
        if (!is_valid_ptr(ptr)) {
            return false;
        }

        // Vérification additionnelle: l'objet doit être dans l'espace mémoire du jeu
        if (module_base && ptr >= module_base && ptr <= (module_base + 0x10000000)) {
            return true;
        }

        // Vérification pour les objets alloués dynamiquement
        if (ptr >= 0x10000000 && ptr <= 0x7FF000000000) {
            return true;
        }

        return false;
    }

    // ⭐ FONCTION BONUS: Validation pour les pointeurs d'armes/équipements
    inline bool is_valid_weapon_ptr(uintptr_t weapon_ptr) {
        if (!is_valid_ptr(weapon_ptr)) {
            return false;
        }

        __try {
            // Vérifier que l'objet a une VTable valide
            uintptr_t vtable = *(uintptr_t*)weapon_ptr;
            if (!is_valid_ptr(vtable)) {
                return false;
            }

            // Vérifier que la VTable pointe vers le module du jeu
            if (module_base && vtable >= module_base && vtable <= (module_base + 0x10000000)) {
                return true;
            }

            return false;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    template<typename t>
    inline t read(DWORD_PTR address, const t& def = t())
    {
        if (valid_pointer(address)) {
            return *(t*)(address);
        }
        return def; // Retourner la valeur par défaut si échec
    }

    template<typename t>
    inline bool write(DWORD_PTR address, const t& value)
    {
        if (valid_pointer(address)) {
            *(t*)(address) = value;
            return true;
        }
        return false;
    }

    inline uint64_t get_module(wchar_t* name) {
        const ntos::peb* peb = reinterpret_cast<ntos::peb*>(__readgsqword(0x60));
        if (!peb) return uint64_t(0);
        const ntos::list_entry head = peb->Ldr->InMemoryOrderModuleList;
        for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink) {
            ntos::ldr_data_table_entry* mod = reinterpret_cast<ntos::ldr_data_table_entry*>(contains_record(curr.Flink, ntos::ldr_data_table_entry, InMemoryOrderLinks));
            if (mod->BaseDllName.Buffer)
                if (crt::wcsicmp_insensitive(mod->BaseDllName.Buffer, name))
                {
                    return uint64_t(mod->DllBase);
                }
        }
        return uint64_t(0);
    }
}