#include "defaultInstructions.hpp"

#include <string>
#include <iostream>

using namespace std;
using namespace KASM;

int _noOp (Instruction&inst, InstructionFrame*frame){
    return 0;
}

//general
int _mov (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _exit (Instruction&inst, InstructionFrame*frame){
    return -1;
}

//math
int _add (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _mult (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _div (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _pow (Instruction&inst, InstructionFrame*frame){
    return -1;
}

//logic
int _cmp (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _jlss (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _jgtr (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _jeql (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _jneql (Instruction&inst, InstructionFrame*frame){
    return -1;
}

//control
int _jmp (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _call (Instruction&inst, InstructionFrame*frame){
    return -1;
}

//stack
int _push (Instruction&inst, InstructionFrame*frame){
    return -1;
}

int _pop (Instruction&inst, InstructionFrame*frame){
    return -1;
}


//default instructions
void KASM::InitInstructionPntrs(InstructionRegistry* reg){
    reg->RegisterInstruction("noop", _noOp);
}