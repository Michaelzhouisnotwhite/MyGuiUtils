#include "MyGuiUtils/common.hpp"
#include <toy/include.h>
#include <windows.h>
#include <string>
#include <vector>

namespace {

static INPUT CreateInput(WORD key, DWORD flags = 0) {
    INPUT input;

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.wScan = 0;
    input.ki.dwFlags = KEYEVENTF_UNICODE | flags;
    input.ki.time = 0;
    input.ki.dwExtraInfo = GetMessageExtraInfo();

    return input;
}
static bool SendInputs(std::vector<INPUT> input) {
    const UINT numberOfAddedEvents = SendInput(input.size(), input.data(), sizeof(INPUT));
    if (numberOfAddedEvents == 0u) {
        return false;
    }

    return true;
}

}  // namespace

namespace GuiUtils {
using std::wstring;
/**
 * @brief Get the Last Visible Active Pop Up Of Window object
 * https://github.com/hluk/CopyQ/blob/master/src/platform/win/winplatform.cpp#L146
 * @param window 
 * @return WINID 
 */
WINID GetLastVisibleActivePopUpOfWindow(WINID window) {
    HWND currentWindow = (HWND)window;

    for (int i = 0; i < 50; ++i) {
        HWND lastPopUp = GetLastActivePopup(currentWindow);

        if (IsWindowVisible(lastPopUp))
            return (WINID)lastPopUp;

        if (lastPopUp == currentWindow)
            return 0;

        currentWindow = lastPopUp;
    }

    return 0;
}
/**
 * @brief Get the Window Class Name object 
 https://github.com/hluk/CopyQ/blob/master/src/platform/win/winplatform.cpp#L146
 * 
 * @param window 
 * @return std::wstring 
 */
std::wstring GetWindowClassName(WINID window) {
    std::array<WCHAR, 32> buf{};
    GetClassNameW((HWND)window, buf.data(), 32);
    return buf.data();
}
/**
 * @brief https://github.com/hluk/CopyQ/blob/master/src/platform/win/winplatform.cpp#L146
 * 
 * @param window 
 * @return true 
 * @return false 
 */
bool IsAltTabWindow(WINID window) {
    if (!window || window == (WINID)GetShellWindow())
        return true;

    HWND root = GetAncestor((HWND)window, GA_ROOTOWNER);

    if (GetLastVisibleActivePopUpOfWindow((WINID)root) != window)
        return true;

    const auto cls = GetWindowClassName(window);
    return cls.empty() || cls == L"Shell_TrayWnd" || cls == L"Shell_SecondaryTrayWnd" ||
           cls == L"Shell_CharmWindow" || cls == L"DV2ControlHost" ||
           cls == L"MsgrIMEWindowClass" || cls == L"SysShadow" || cls == L"Button" ||
           cls.rfind(L"WMP9MediaBarFlyout") != cls.npos;
}

void SetForegroundWindow(WINID wnd_id, StatusCode& err) {
    auto wnd_ptr = (HWND)wnd_id;
    auto res = ::SetForegroundWindow(wnd_ptr);
    err = res ? StatusCode::PASS : StatusCode::SetForegroundWindowFailed;
}
WINID GetForegroundWinId(StatusCode& err) {
    auto res = ::GetForegroundWindow();
    if (!res) {
        err = StatusCode::GetForegroundWinIdFailed;
    }
    err = StatusCode::PASS;
    return (uint64_t)res;
}
void Paste2ForeGroundWindow(StatusCode& error) {
    error = StatusCode::PASS;
    bool state = SendInputs({CreateInput(VK_LSHIFT), CreateInput(VK_INSERT),
                             CreateInput(VK_LSHIFT, KEYEVENTF_KEYUP),
                             CreateInput(VK_INSERT, KEYEVENTF_KEYUP)});
    if (state) {
        error = StatusCode::PasteError;
    }
}
void Input2ForeGroundWindow(const std::string& content) {
    std::vector<INPUT> inputs;
    toy::enumerate(content, [&inputs](const auto& i, const auto& letter) {
        if (!IsAscii(letter)) {
            return false;
        }
        if (IsCapLetter(letter)) {
            inputs.push_back(CreateInput(VK_LSHIFT));
            inputs.push_back(CreateInput(letter));
            inputs.push_back(CreateInput(VK_LSHIFT, KEYEVENTF_KEYUP));
        } else if (IsLowLetter(letter)) {
            inputs.push_back(CreateInput(ToUpperCase(letter)));
        } else {
            inputs.push_back(CreateInput(letter));
        }
        return false;
    });
    SendInputs(inputs);
}
}  // namespace GuiUtils
