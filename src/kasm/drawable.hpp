#ifndef KASM_DRAWABLE
#define KASM_DRAWABLE

#include "../kasm/procdefs.hpp"

namespace KASM{
    class AsmController;
namespace GRAPHICS{
    void InitGraphics(AsmController&);
    void StartGlobals();
}}

#endif