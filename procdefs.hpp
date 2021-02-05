#ifndef KASM_PROCDEF
#define KASM_PROCDEF

#include "err.hpp"

namespace KASM{
    struct Instruction;
    class InstructionFrame;
    typedef ErrCode (*InstructionProc)(Instruction&, InstructionFrame*);
}

#endif