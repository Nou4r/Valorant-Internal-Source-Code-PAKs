#pragma once
#include <thread>
#include <chrono>
#include <array>
#include <cstring>
#include <string>
#include <type_traits>
#include <iostream>
#include <comutil.h>
#include <immintrin.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "crypt32.lib")

#ifdef _KERNEL_MODE
namespace std {
    template <class _Ty> struct remove_reference { using type = _Ty; };
    template <class _Ty> struct remove_reference<_Ty&> { using type = _Ty; };
    template <class _Ty> struct remove_reference<_Ty&&> { using type = _Ty; };
    template <class _Ty> using remove_reference_t = typename remove_reference<_Ty>::type;

    template <class _Ty> struct remove_const { using type = _Ty; };
    template <class _Ty> struct remove_const<const _Ty> { using type = _Ty; };
    template <class _Ty> using remove_const_t = typename remove_const<_Ty>::type;
}
#else
#include <type_traits>
#endif

namespace skc {
    __forceinline void secure_memzero(void* buf, size_t len) {
#if defined(_WIN32) || defined(_WIN64)
        SecureZeroMemory(buf, len);
#else
        volatile unsigned char* p = reinterpret_cast<volatile unsigned char*>(buf);
        while (len--) *p++ = 0;
#endif
    }

    __forceinline void lock_memory(void* ptr, size_t size) {
#if defined(_WIN32) || defined(_WIN64)
        VirtualLock(ptr, size);
#endif
    }

    __forceinline void unlock_memory(void* ptr, size_t size) {
#if defined(_WIN32) || defined(_WIN64)
        VirtualUnlock(ptr, size);
#endif
    }

    namespace crypto {
        constexpr uint64_t constexpr_prng(uint64_t seed) {
            seed = (seed ^ 0x9E3779B97F4A7C15ull) * 0xBF58476D1CE4E5B9ull;
            seed = (seed ^ (seed >> 31)) * 0x94D049BB133111EBull;
            seed = (seed ^ (seed >> 27)) * 0xBF58476D1CE4E5B9ull;
            seed = (seed ^ (seed >> 30)) * 0x94D049BB133111EBull;
            return seed ^ (seed >> 31);
        }

        constexpr uint64_t generate_position_key(uint64_t base_key, uint64_t position) {
            uint64_t key = base_key ^ position;
            key = constexpr_prng(key);
            key = (key >> 16) | (key << 48);
            key = key ^ (0x5A8279995A827999ull + position);
            key = constexpr_prng(key);
            key = (key >> 24) | (key << 40);
            key = key ^ (0x6ED9EBA16ED9EBA1ull - position);
            key = constexpr_prng(key);
            key = (key >> 32) | (key << 32);
            key = key ^ (0x8F1BBCDC8F1BBCDCull + position);
            return constexpr_prng(key);
        }

        constexpr uint8_t encrypt_byte(uint8_t byte, uint64_t key, uint64_t position) {
            uint8_t subkeys[8];
            for (int i = 0; i < 8; i++) {
                subkeys[i] = static_cast<uint8_t>((key >> (i * 8)) & 0xFF);
            }

            for (int round = 0; round < 8; round++) {
                uint8_t round_key = subkeys[round % 8] ^ static_cast<uint8_t>(position + round);

                switch (round % 8) {
                case 0: byte = (byte ^ round_key) + 0x3F; break;
                case 1: byte = (byte + round_key) ^ 0xAA; break;
                case 2: byte = ((byte << 4) | (byte >> 4)) ^ round_key; break;
                case 3: byte = (byte ^ 0x55) - round_key; break;
                case 4: byte = (byte + 0x22) ^ (round_key << 1); break;
                case 5: byte = ((byte >> 3) | (byte << 5)) ^ round_key; break;
                case 6: byte = (byte ^ round_key) + position; break;
                case 7: byte = byte ^ (round_key + 0x77); break;
                }
            }

            return byte;
        }

        constexpr uint8_t decrypt_byte(uint8_t byte, uint64_t key, uint64_t position) {
            uint8_t subkeys[8];
            for (int i = 0; i < 8; i++) {
                subkeys[i] = static_cast<uint8_t>((key >> (i * 8)) & 0xFF);
            }

            for (int round = 7; round >= 0; round--) {
                uint8_t round_key = subkeys[round % 8] ^ static_cast<uint8_t>(position + round);

                switch (round % 8) {
                case 7: byte = byte ^ (round_key + 0x77); break;
                case 6: byte = (byte - position) ^ round_key; break;
                case 5: byte = ((byte ^ round_key) << 3) | ((byte ^ round_key) >> 5); break;
                case 4: byte = (byte ^ (round_key << 1)) - 0x22; break;
                case 3: byte = (byte + round_key) ^ 0x55; break;
                case 2: byte = ((byte ^ round_key) >> 4) | ((byte ^ round_key) << 4); break;
                case 1: byte = (byte ^ 0xAA) - round_key; break;
                case 0: byte = (byte - 0x3F) ^ round_key; break;
                }
            }

            return byte;
        }
    }

    template<class _Ty>
    using clean_type = typename std::remove_const_t<std::remove_reference_t<_Ty>>;

    template <int _size, char _key1, char _key2, typename T>
    class crypter {
    private:
        T _storage[_size]{};
        mutable bool encrypted{ true };

        __forceinline static constexpr uint64_t get_base_key() {
            return (static_cast<uint64_t>(_key1) << 56) |
                (static_cast<uint64_t>(_key2) << 48) |
                (static_cast<uint64_t>(_key1) << 40) |
                (static_cast<uint64_t>(_key2) << 32) |
                (static_cast<uint64_t>(_key1) << 24) |
                (static_cast<uint64_t>(_key2) << 16) |
                (static_cast<uint64_t>(_key1) << 8) |
                static_cast<uint64_t>(_key2);
        }

        __forceinline void decrypt_to(T* buffer) const {
            uint64_t base_key = get_base_key();

            for (int i = 0; i < _size; i++) {
                uint64_t position_key = crypto::generate_position_key(base_key, i);
                buffer[i] = static_cast<T>(crypto::decrypt_byte(
                    static_cast<uint8_t>(_storage[i]), position_key, i));
            }
        }

    public:
        __forceinline constexpr crypter(T* data) {
            uint64_t base_key = get_base_key();

            for (int i = 0; i < _size; i++) {
                uint64_t position_key = crypto::generate_position_key(base_key, i);
                _storage[i] = static_cast<T>(crypto::encrypt_byte(
                    static_cast<uint8_t>(data[i]), position_key, i));
            }
        }

        __forceinline T* get() { return _storage; }
        __forceinline int size() { return _size; }
        __forceinline char key() { return _key1; }

        __forceinline T* encrypt() {
            if (!encrypted) {
                uint64_t base_key = get_base_key();
                for (int i = 0; i < _size; i++) {
                    uint64_t position_key = crypto::generate_position_key(base_key, i);
                    _storage[i] = static_cast<T>(crypto::encrypt_byte(
                        static_cast<uint8_t>(_storage[i]), position_key, i));
                }
                encrypted = true;
            }
            return _storage;
        }

        __forceinline T* decrypt() {
            if (encrypted) {
                uint64_t base_key = get_base_key();
                for (int i = 0; i < _size; i++) {
                    uint64_t position_key = crypto::generate_position_key(base_key, i);
                    _storage[i] = static_cast<T>(crypto::decrypt_byte(
                        static_cast<uint8_t>(_storage[i]), position_key, i));
                }
                encrypted = false;
            }
            return _storage;
        }

        __forceinline bool isEncrypted() const { return encrypted; }

        __forceinline std::string decrypt_and_wipe() {
            T decryptedBuffer[512];
            const size_t buffer_size = (_size < 512) ? _size : 512;

            decrypt_to(decryptedBuffer);

            std::string result;
            for (int i = 0; i < buffer_size - 1; i++) {
                result += static_cast<char>(decryptedBuffer[i]);
            }

            secure_memzero(decryptedBuffer, sizeof(decryptedBuffer));

            return result;
        }

        __forceinline std::wstring decrypt_and_wipe_w() {
            T decryptedBuffer[512];
            const size_t buffer_size = (_size < 512) ? _size : 512;

            decrypt_to(decryptedBuffer);

            std::wstring result;
            for (int i = 0; i < buffer_size - 1; i++) {
                result += static_cast<wchar_t>(decryptedBuffer[i]);
            }

            secure_memzero(decryptedBuffer, sizeof(decryptedBuffer));

            return result;
        }

        __forceinline const char* decrypt_and_wipe_cstr() {
            static thread_local char decryptedBuffer[512];
            const size_t buffer_size = (_size < 512) ? _size : 512;

            T tempBuffer[512];
            decrypt_to(tempBuffer);

            for (size_t i = 0; i < buffer_size - 1; i++) {
                decryptedBuffer[i] = static_cast<char>(tempBuffer[i]);
            }
            decryptedBuffer[buffer_size - 1] = '\0';

            secure_memzero(tempBuffer, sizeof(tempBuffer));

            return decryptedBuffer;
        }

        __forceinline const wchar_t* decrypt_and_wipe_wc_str() {
            static thread_local wchar_t decryptedBuffer[512];
            const size_t buffer_size = (_size < 512) ? _size : 512;

            T tempBuffer[512];
            decrypt_to(tempBuffer);

            for (size_t i = 0; i < buffer_size - 1; i++) {
                decryptedBuffer[i] = static_cast<wchar_t>(tempBuffer[i]);
            }
            decryptedBuffer[buffer_size - 1] = L'\0';

            secure_memzero(tempBuffer, sizeof(tempBuffer));

            return decryptedBuffer;
        }

        __forceinline void clear() {
            secure_memzero(_storage, sizeof(_storage));
            encrypted = false;
        }

        __forceinline std::string str() {
            return decrypt_and_wipe();
        }

        __forceinline std::wstring wstr() {
            return decrypt_and_wipe_w();
        }

        __forceinline const char* c_str() {
            return decrypt_and_wipe_cstr();
        }

        __forceinline const wchar_t* wc_str() {
            return decrypt_and_wipe_wc_str();
        }

        template<typename U = T, typename std::enable_if<std::is_same<U, char>::value, int>::type = 0>
        __forceinline operator const char* () { return c_str(); }

        template<typename U = T, typename std::enable_if<std::is_same<U, wchar_t>::value, int>::type = 0>
        __forceinline operator const wchar_t* () { return wc_str(); }

        __forceinline operator _bstr_t() {
            if constexpr (std::is_same_v<T, wchar_t>) {
                return _bstr_t(wc_str());
            }
            else {
                return _bstr_t(c_str());
            }
        }

        friend std::ostream& operator<<(std::ostream& os, crypter& obj) {
            os << obj.c_str(); return os;
        }
        friend std::wostream& operator<<(std::wostream& os, crypter& obj) {
            os << obj.wc_str(); return os;
        }
    };
}

#define crypt(str) crypt_key(str, __TIME__[4], __TIME__[7])
#define crypt_key(str, key1, key2) []() { \
    constexpr static auto crypted = skc::crypter \
        <sizeof(str) / sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>((skc::clean_type<decltype(str[0])>*)str); \
    return crypted; }()