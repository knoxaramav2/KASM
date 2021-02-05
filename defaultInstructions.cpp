#include "defaultInstructions.hpp"
#include "mem.hpp"
#include "ops.hpp"
#include "err.hpp"

#include <string>
#include <iostream>

using namespace std;
using namespace KASM;

ErrCode _noOp (Instruction&inst, InstructionFrame*frame){
    return ERR_OK;
}

//general
ErrCode _mov (Instruction&inst, InstructionFrame*frame){
    
    return ERR_UNIMPLEMENTED;
}

ErrCode _exit (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//math
ErrCode _add (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _mult (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _div (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _pow (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//logic
ErrCode _cmp (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _jlss (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _jgtr (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _jeql (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _jneql (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//control
ErrCode _jmp (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _call (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//stack
ErrCode _push (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _pop (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//High level
ErrCode _prnt (Instruction&inst, InstructionFrame*frame){
    
    if (inst.Rv0->type != KT_STRING){
        return ERR_TYPE_MISMATCH;
    }

    return ERR_OK;
}

ErrCode _goxy (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _clr (Instruction&inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//default instructions
void KASM::InitInstructionPntrs(InstructionRegistry* reg){
    reg->RegisterInstruction("noop", _noOp);

    reg->RegisterInstruction("mov", _mov);
    reg->RegisterInstruction("exit", _exit);

    reg->RegisterInstruction("add", _add);
    reg->RegisterInstruction("mult", _mult);
    reg->RegisterInstruction("div", _div);
    reg->RegisterInstruction("pow", _pow);

    reg->RegisterInstruction("cmp", _cmp);
    reg->RegisterInstruction("jlss", _jlss);
    reg->RegisterInstruction("jgtr", _jgtr);
    reg->RegisterInstruction("jeql", _jeql);
    reg->RegisterInstruction("jneql", _jneql);

    reg->RegisterInstruction("jmp", _jmp);
    reg->RegisterInstruction("call", _call);

    reg->RegisterInstruction("push", _push);
    reg->RegisterInstruction("pop", _pop);
}