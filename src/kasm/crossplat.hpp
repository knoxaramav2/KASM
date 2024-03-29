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

            enum TerminalWH{
                WIDTH, HEIGHT
            };

            enum TerminalXY{
                XPOS, YPOS
            };

            void InitTerminalAttr();
            bool SetCursorXY(int x, int y);
            int GetCursorXY(TerminalXY);
            bool SetColor(int foreGround, int backGround);
            void ClearColor();
            bool PlotXY(int x, int y, std::string str);
            bool ReizeTerminal(int x, int y);
            int GetTerminalDim(TerminalWH ta);
        }
    }
}


#endif