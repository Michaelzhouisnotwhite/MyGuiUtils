#include <cstdio>
#include <thread>
#include "MyGuiUtils/common.hpp"
#include <array>
using namespace std::literals;
#ifdef WIN32
#include <windows.h>
int main(int args, char* argv[]) {
    GuiUtils::WINID win_id = 0;
    while (true) {
        auto temp_id = GuiUtils::GetForegroundWinId(GuiUtils::status_code_);
        if (temp_id != win_id) {
            std::array<WCHAR, 32> buf{};
            GetClassNameW((HWND)temp_id, buf.data(), 32);
            printf("class name: %s:%s ", GuiUtils::WStr2Str(buf.data()).c_str());
            printf("winid %ld ", temp_id);
            printf("Is alt tab window: %s\n",
                   (GuiUtils::IsAltTabWindow(temp_id) ? "true" : "false"));
            win_id = temp_id;
        }
        std::this_thread::sleep_for(100ms);
    }
    return 0;
}
#endif