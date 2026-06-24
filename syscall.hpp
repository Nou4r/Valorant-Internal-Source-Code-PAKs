// syscall.hpp
#pragma once
#include <Windows.h>

__forceinline NTSTATUS sys_alloc(HANDLE p, PVOID* addr, SIZE_T size, ULONG prot) {
    static FARPROC ntAlloc = GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtAllocateVirtualMemory");
    return ((NTSTATUS(NTAPI*)(HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG))ntAlloc)
        (p, addr, 0, &size, MEM_COMMIT | MEM_RESERVE, prot);
}