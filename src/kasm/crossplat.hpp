#ifndef KASM_CROSS
#define KASM_CROSS

#include <string>

#ifdef __WINDOWS
    //#error Windows support not implemented yet
    //#define EL "\r\n"
#else
    #define EL "\n"
#endif

namespace KASM{
    namespace KCompat{
        namespace String{
            std::string FormatPath(std::string path);
        }

        namespace Graphics{
            bool SetCursorXY(int x, int y);
            bool SetColor(int foreGround, int backGround);
            bool PlotXY(int x, int y, char c);
            bool ReizeTerminal(int x, int y);
        }
    }
}


#endif