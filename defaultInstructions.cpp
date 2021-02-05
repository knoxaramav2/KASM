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
    
    MemItem * i1 = inst.Rv0;
    MemItem * i2 = inst.Rv1;

    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    switch (i1->type)
    {
    case KT_INT: *(int*)i2->data = *((int*)i1->data); break;
    
    default:
        break;
    }

    return ERR_OK;
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

    //TODO - replace with crossplat UI calls
    switch(inst.Rv0->type){
        case KT_INT:
        cout << *(int*)inst.Rv0->data;
        break;
        case KT_FLOAT:
        cout << *(float*)inst.Rv0->data;
        break;
        case KT_CHAR:
        cout << *(signed char*)inst.Rv0->data;
        break;
        case KT_BYTE:
        cout << *(unsigned char*)inst.Rv0->data;
        break;
        case KT_STRING:
        cout << *(string*)inst.Rv0->data;
        break;
        default:
        return ERR_TYPE_MISMATCH;
        break;
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

    reg->RegisterInstruction("prnt", +_prnt);
    reg->RegisterInstruction("goxy", _goxy);
    reg->RegisterInstruction("clr", _clr);


}