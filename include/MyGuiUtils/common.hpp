#ifndef INCLUDE_MYGUIUTILS_COMMON
#define INCLUDE_MYGUIUTILS_COMMON
#include <cstdint>
#include <string>
namespace GuiUtils {
enum class KeyAction { UP, DOWN };
enum class StatusCode { PASS, PasteError, InputError, SetForegroundWindowFailed, GetForegroundWinIdFailed };
static StatusCode status_code_ = StatusCode::PASS;
void InputToForeGroundWindow(const std::string&);
void PasteToForeGroundWindow(StatusCode& error);

}  // namespace GuiUtils
// #ifdef WIN32
// #include <windows.h>
namespace GuiUtils {
void SetForegroundWindow(uint64_t wnd_id, StatusCode&);
uint64_t GetForegroundWinId(StatusCode&);
}  // namespace GuiUtils
// #endif
#endif /* INCLUDE_MYGUIUTILS_COMMON */
