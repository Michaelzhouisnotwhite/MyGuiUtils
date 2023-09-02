#include <toy/include.h>
#include <windows.h>
#include <string>
#include <vector>
#include "MyGuiUtils/common.hpp"

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
static bool IsCapLetter(const char& letter) {
    return letter <= 'Z' && letter >= 'A';
}
static bool IsLowLetter(const char& letter) {
    return letter <= 'z' && letter >= 'a';
}
template <typename CharType>
static bool IsAscii(const CharType& letter) {
    return ((int8_t)letter <= 127 && letter >= 0);
}
static char ToUpperCase(const char& letter) {
    if (IsLowLetter(letter)) {
        return (char)(letter - 'a' + 'A');
    }
    return letter;
}
}  // namespace

namespace GuiUtils {
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
void PasteToForeGroundWindow(StatusCode& error) {
    error = StatusCode::PASS;
    bool state = SendInputs({CreateInput(VK_LSHIFT), CreateInput(VK_INSERT),
                             CreateInput(VK_LSHIFT, KEYEVENTF_KEYUP),
                             CreateInput(VK_INSERT, KEYEVENTF_KEYUP)});
    if (state) {
        error = StatusCode::PasteError;
    }
}
void InputToForeGroundWindow(const std::string& content) {
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
