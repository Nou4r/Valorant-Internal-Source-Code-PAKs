inline bool IsDebuggerPresent2() {
    BOOL bDebug = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &bDebug);
    return bDebug || IsDebuggerPresent();
}