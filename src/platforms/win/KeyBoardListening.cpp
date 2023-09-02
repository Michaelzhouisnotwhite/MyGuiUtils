#include "MyGuiUtils/common.hpp"
// static HHOOK hook = nullptr;
// HINSTANCE hin;
// LRESULT CALLBACK key_hook_proc(int code, WPARAM wParam, LPARAM lParam) {
//     if (code < 0) {
//         return CallNextHookEx(hook, code, wParam, lParam);
//     }   
//     auto keyHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
//     WORD vkCode = LOWORD(wParam);
//     WORD keyFlags = HIWORD(lParam);
//     if ((keyFlags & WM_KEYDOWN) == WM_KEYDOWN) {
//         std::puts("key down");
//     }
//     if ((keyFlags & WM_KEYUP) == WM_KEYUP) {
//         puts("key up");
//     }
//     switch (vkCode) {
//         case VK_SHIFT: {
//             puts("shift");
//             break;
//         }
//         case 'A': {
//             puts("A");
//             break;
//         }
//     }
//     return CallNextHookEx(hook, code, wParam, lParam);
//     ;
// }

// void InstallHook() {
//     hook = SetWindowsHookExA(WH_KEYBOARD, key_hook_proc, nullptr, 0);
//     //    hook = SetWindowsHook(WH_KEYBOARD, key_hook_proc);
// }
