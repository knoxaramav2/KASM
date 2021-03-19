#ifndef KASM_DRAWABLE
#define KASM_DRAWABLE

#include "../kasm/procdefs.hpp"

#include <ncurses.h>

namespace KASM{
    class AsmController;
namespace GRAPHICS{
    void InitGraphics(AsmController&);
    void StartGlobals();
}}

#endif