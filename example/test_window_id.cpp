#include <cstdio>
#include <thread>
#include "MyGuiUtils/common.hpp"
using namespace std::literals;
#ifdef WIN32
#include <windows.h>
int main(int args, char* argv[])
{
    HWND win_id = nullptr;
    while (true) {
        auto temp_id = GuiUtils::GetForegroundWinId(GuiUtils::status_code_);
        if(temp_id != win_id) {
            printf("%p\n", temp_id);
            win_id = temp_id;
        }
        std::this_thread::sleep_for(100ms);
    }
    return 0;
}
#endif