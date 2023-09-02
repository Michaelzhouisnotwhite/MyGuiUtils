#include "MyGuiUtils/common.hpp"

#ifdef WIN32
#include <windows.h>
int main(int args, char* argv[])
{
    SetForegroundWindow((HWND)0x0000000000020ce8);
    GuiUtils::Input2ForeGroundWindow("input abcasdf");
    return 0;
}   
#endif