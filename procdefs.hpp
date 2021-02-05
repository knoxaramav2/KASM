#ifndef KASM_PROCDEF
#define KASM_PROCDEF

namespace KASM{
    struct Instruction;
    class InstructionFrame;
    typedef int (*InstructionProc)(Instruction&, InstructionFrame*);
}

#endif