// Handleprocces.hpp
#pragma once
#include <Windows.h>

inline void HideHandle() {
    HANDLE hProc = GetCurrentProcess();
    SetHandleInformation(hProc, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
}