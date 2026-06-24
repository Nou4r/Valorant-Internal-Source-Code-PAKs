#pragma once
#include <windows.h>
#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>

// ═══════════════════════════════════════════════════════
//  PAK MOD MOUNTER — Valorant custom character skins
//  Offsets: versiyon bağımlı, güncellenmesi gerekebilir
// ═══════════════════════════════════════════════════════

namespace pak_mods {

    // PAK dosyaları bu klasörden yüklenir
    static constexpr wchar_t MOD_DIR[] = L"C:\\mods\\";

    // ── Güncel Offset'ler ──
    static constexpr uintptr_t OFF_FPAK_DELEGATE = 0xC0FBA38; // FPakPlatformFile ptr
    static constexpr uintptr_t OFF_SIGN_DELEGATE = 0xC4472A8; // İmza bypass
    static constexpr uintptr_t OFF_MOUNT_FN = 0x282CC50; // Mount fonksiyonu

    // FPakPlatformFile pointer'ını döndür
    static __int64 get_fpak() {
        uintptr_t base = (uintptr_t)GetModuleHandleA(nullptr);
        __int64 delegate = *(__int64*)(base + OFF_FPAK_DELEGATE);
        if (!delegate) return 0;
        return *(__int64*)(delegate + 24);
    }

    // İmza doğrulamasını bypass et
    static void bypass_signing() {
        uintptr_t base = (uintptr_t)GetModuleHandleA(nullptr);
        auto sign_ptr = (uint8_t*)(base + OFF_SIGN_DELEGATE);

        DWORD old = 0;
        VirtualProtect(sign_ptr, 0x20, PAGE_READWRITE, &old);
        memset(sign_ptr, 0, 0x20);
        VirtualProtect(sign_ptr, 0x20, old, &old);

        __int64 fpak = get_fpak();
        if (fpak) {
            auto bsigned = (uint8_t*)(fpak + 48);
            VirtualProtect(bsigned, 1, PAGE_READWRITE, &old);
            *bsigned = 0;
            VirtualProtect(bsigned, 1, old, &old);
        }
    }

    // Tek bir PAK dosyasını yükle
    static bool mount_pak(const wchar_t* path, int priority) {
        __int64 fpak = get_fpak();
        if (!fpak) return false;

        typedef bool(__fastcall* fn_mount)(
            __int64, const wchar_t*, int, const wchar_t*, bool, bool);

        uintptr_t base = (uintptr_t)GetModuleHandleA(nullptr);
        auto mount = (fn_mount)(base + OFF_MOUNT_FN);
        return mount(fpak, path, priority, nullptr, true, false);
    }

    // Mods klasöründeki tüm .pak dosyalarını yükle
    static void mount_all() {
        bypass_signing();

        // Önce exe yanındaki mods klasörünü dene (DLL ile aynı dizin)
        wchar_t dll_path[MAX_PATH] = {};
        GetModuleFileNameW(nullptr, dll_path, MAX_PATH);

        // exe'nin bulunduğu dizindeki mods klasörü
        std::wstring base_dir(dll_path);
        auto last_slash = base_dir.rfind(L'\\');
        if (last_slash != std::wstring::npos)
            base_dir = base_dir.substr(0, last_slash + 1);

        // Arama sırası: masaüstü → exe yanı → sabit C:\mods
        std::vector<std::wstring> search_dirs = {
            L"C:\\Users\\m\\Desktop\\mods\\",
            base_dir + L"mods\\",
            L"C:\\mods\\"
        };

        int priority = 10000;
        bool any_mounted = false;

        for (auto& dir : search_dirs) {
            if (!std::filesystem::exists(dir)) continue;

            for (auto& entry : std::filesystem::directory_iterator(dir)) {
                if (entry.path().extension() != L".pak") continue;

                std::wstring pak_path = entry.path().wstring();
                bool ok = mount_pak(pak_path.c_str(), priority++);
                if (ok) any_mounted = true;
            }
            if (any_mounted) break;
        }
    }

} // namespace pak_mods
