#ifndef INCLUDE_MYGUIUTILS_COMMON
#define INCLUDE_MYGUIUTILS_COMMON
#include <cstdint>
#include <string>
namespace GuiUtils {
using WINID = uint64_t ;
enum class KeyAction { UP, DOWN };
enum class StatusCode { PASS, PasteError, InputError, SetForegroundWindowFailed, GetForegroundWinIdFailed };
static StatusCode status_code_ = StatusCode::PASS;
void InputToForeGroundWindow(const std::string&);
void PasteToForeGroundWindow(StatusCode& error);

}  // namespace GuiUtils
// #ifdef WIN32
// #include <windows.h>
namespace GuiUtils {
void SetForegroundWindow(WINID wnd_id, StatusCode&);
WINID GetForegroundWinId(StatusCode&);
}  // namespace GuiUtils
// #endif
#endif /* INCLUDE_MYGUIUTILS_COMMON */
