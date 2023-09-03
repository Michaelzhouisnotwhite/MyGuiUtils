#ifndef INCLUDE_MYGUIUTILS_COMMON
#define INCLUDE_MYGUIUTILS_COMMON
#include <codecvt>
#include <cstdint>
#include <locale>
#include <string>
namespace GuiUtils {
using WINID = uint64_t;
enum class KeyAction { UP, DOWN };
enum class StatusCode {
    PASS,
    PasteError,
    InputError,
    SetForegroundWindowFailed,
    GetForegroundWinIdFailed
};
static StatusCode status_code_ = StatusCode::PASS;
void Input2ForeGroundWindow(const std::string&);
void Paste2ForeGroundWindow(StatusCode& error);

void SetForegroundWindow(WINID wnd_id, StatusCode&);
WINID GetForegroundWinId(StatusCode&);
bool IsAltTabWindow(WINID window);
inline std::wstring Str2WStr(const std::string& str) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

inline std::string WStr2Str(const std::wstring& wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
inline bool IsCapLetter(const char& letter) {
    return letter <= 'Z' && letter >= 'A';
}
inline bool IsLowLetter(const char& letter) {
    return letter <= 'z' && letter >= 'a';
}
template <typename CharType>
inline bool IsAscii(const CharType& letter) {
    return ((uint8_t)letter <= 127 && letter >= 0);
}
inline char ToUpperCase(const char& letter) {
    if (IsLowLetter(letter)) {
        return (char)(letter - 'a' + 'A');
    }
    return letter;
}
bool IsKeyPressed(int key);
bool IsModifierPressed();
}  // namespace GuiUtils
// #endif
#endif /* INCLUDE_MYGUIUTILS_COMMON */
