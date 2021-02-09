#include "defaultInstructions.hpp"
#include "mem.hpp"
#include "ops.hpp"
#include "err.hpp"

#include <string>
#include <iostream>
#include <math.h>

using namespace std;
using namespace KASM;

#define NA_MISMATCH(t1, t2) ((t1 != KT_STRING) && (t2 == KT_STRING))

//Check if typical conversion possible
//Checks for T1->T2
//(prevent illegal string operations)
bool TypeCompatible(KASMType t1, KASMType t2){
    return !(NA_MISMATCH(t1,t2) || NA_MISMATCH(t2, t1));
}

//******** Template operations
//******** Type arguments used for guarding illegal conversions or special conversions
//Operations are: rv1->rv2

template <class T1, class T2>
bool CopyMem(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return false;}
    *(T2*)rv = *((T1*)lv);
    return true;
}

template <class T1, class T2>
bool Sum(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return false;}
    *(T2*)rv += *((T1*)lv);
    return true;
}

template <class T1, class T2>
bool Mlt(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return false;}
    *(T2*)rv *= *((T1*)lv);
    return true;
}

template <class T1, class T2>
bool Div(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return false;}
    *(T2*)rv /= *((T1*)lv);
    return true;
}

template <class T1, class T2>
bool Pow(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return false;}
    *(T2*)rv = pow(*((T2*)rv), *((T1*)lv));
    return true;
}

template <class T1, class T2>
int Cmp(void* lv, void* rv, KASMType t1, KASMType t2){
    if (!TypeCompatible(t1, t2)) {return -2;}
    return *(T2*)rv - *((T1*)lv);
}

//*******************************************


ErrCode _noOp (Instruction*inst, InstructionFrame*frame){
    return ERR_OK;
}

ErrCode _label (Instruction*inst, InstructionFrame*frame){
    return ERR_OK;
}

//general
ErrCode _mov (Instruction*inst, InstructionFrame*frame){
    
    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    switch (i1->type)
    {
    case KT_INT:    *(int*)i2->data = *((int*)i1->data); break;
    case KT_FLOAT:  *(float*)i2->data = *((float*)i1->data); break;
    case KT_BYTE:   *(unsigned char*)i2->data = *((unsigned int*)i1->data); break;
    case KT_CHAR:   *(char*)i2->data = *((char*)i1->data); break;
    case KT_STRING: *(string*)i2->data = *((string*)i1->data); break;
    default:
        break;
    }

    return ERR_OK;
}

ErrCode _exit (Instruction*inst, InstructionFrame*frame){
    
    if (inst->Rv0 != nullptr){
        if (inst->Rv0->type == KT_INT) {
            MemItem* mi = frame->GetRegisters()->GetRegister("rir");
            *(int*)mi->data = *((int*)inst->Rv0->data);
        } else if (inst->Rv0->type == KT_FLOAT){
            MemItem* mi = frame->GetRegisters()->GetRegister("rfr");
            *(float*)mi->data = *((float*)inst->Rv0->data);
        } else {
            return ERR_TYPE_MISMATCH;
        }
    }

    frame->SetExit();

    return ERR_OK;
}

//math
ErrCode _add (Instruction*inst, InstructionFrame*frame){
    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    //two operators requires (value, register)
    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    //rval 2 cannot be const
    if (i2->isConst){
        return ERR_ILLEGAL_ARG;
    }

    KASMType t1, t2;
    t1 = i1->type;
    t2 = i2->type;

    if (t1==KT_INT && t2==KT_INT){Sum<int, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_FLOAT){Sum<int, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_CHAR){Sum<int, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_BYTE){Sum<int, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_FLOAT && t2==KT_INT){Sum<float, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_FLOAT){Sum<float, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_CHAR){Sum<float, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_BYTE){Sum<float, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_CHAR && t2==KT_INT){Sum<char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_FLOAT){Sum<char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_CHAR){Sum<char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_BYTE){Sum<char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_BYTE && t2==KT_INT){Sum<unsigned char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_FLOAT){Sum<unsigned char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_CHAR){Sum<unsigned char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_BYTE){Sum<unsigned char, unsigned char>(i1->data, i2->data, t1, t2);}

    else {return ERR_ILLEGAL_ARG;}

    return ERR_OK;
}

ErrCode _mult (Instruction*inst, InstructionFrame*frame){
    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    //two operators requires (value, register)
    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    //rval 2 cannot be const
    if (i2->isConst){
        return ERR_ILLEGAL_ARG;
    }

    KASMType t1, t2;
    t1 = i1->type;
    t2 = i2->type;

    if (t1==KT_INT && t2==KT_INT){Mlt<int, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_FLOAT){Mlt<int, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_CHAR){Mlt<int, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_BYTE){Mlt<int, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_FLOAT && t2==KT_INT){Mlt<float, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_FLOAT){Mlt<float, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_CHAR){Mlt<float, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_BYTE){Mlt<float, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_CHAR && t2==KT_INT){Mlt<char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_FLOAT){Mlt<char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_CHAR){Mlt<char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_BYTE){Mlt<char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_BYTE && t2==KT_INT){Mlt<unsigned char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_FLOAT){Mlt<unsigned char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_CHAR){Mlt<unsigned char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_BYTE){Mlt<unsigned char, unsigned char>(i1->data, i2->data, t1, t2);}

    else {return ERR_ILLEGAL_ARG;}

    return ERR_OK;
}

ErrCode _div (Instruction*inst, InstructionFrame*frame){
    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    //two operators requires (value, register)
    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    //rval 2 cannot be const
    if (i2->isConst){
        return ERR_ILLEGAL_ARG;
    }

    KASMType t1, t2;
    t1 = i1->type;
    t2 = i2->type;

    if (t1==KT_INT && t2==KT_INT){Div<int, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_FLOAT){Div<int, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_CHAR){Div<int, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_BYTE){Div<int, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_FLOAT && t2==KT_INT){Div<float, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_FLOAT){Div<float, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_CHAR){Div<float, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_BYTE){Div<float, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_CHAR && t2==KT_INT){Div<char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_FLOAT){Div<char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_CHAR){Div<char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_BYTE){Div<char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_BYTE && t2==KT_INT){Div<unsigned char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_FLOAT){Div<unsigned char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_CHAR){Div<unsigned char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_BYTE){Div<unsigned char, unsigned char>(i1->data, i2->data, t1, t2);}

    else {return ERR_ILLEGAL_ARG;}

    return ERR_OK;
}

ErrCode _pow (Instruction*inst, InstructionFrame*frame){
    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    //two operators requires (value, register)
    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    //rval 2 cannot be const
    if (i2->isConst){
        return ERR_ILLEGAL_ARG;
    }

    KASMType t1, t2;
    t1 = i1->type;
    t2 = i2->type;

    if (t1==KT_INT && t2==KT_INT){Pow<int, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_FLOAT){Pow<int, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_CHAR){Pow<int, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_BYTE){Pow<int, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_FLOAT && t2==KT_INT){Pow<float, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_FLOAT){Pow<float, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_CHAR){Pow<float, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_BYTE){Pow<float, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_CHAR && t2==KT_INT){Pow<char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_FLOAT){Pow<char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_CHAR){Pow<char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_BYTE){Pow<char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_BYTE && t2==KT_INT){Pow<unsigned char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_FLOAT){Pow<unsigned char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_CHAR){Pow<unsigned char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_BYTE){Pow<unsigned char, unsigned char>(i1->data, i2->data, t1, t2);}

    else {return ERR_ILLEGAL_ARG;}

    return ERR_OK;
}

//logic
ErrCode _cmp (Instruction*inst, InstructionFrame*frame){

    MemItem * reg = frame->GetRegisters()->GetRegister("cmr");
    int res = 0;

    MemItem * i1 = inst->Rv0;
    MemItem * i2 = inst->Rv1;

    //two operators requires (value, register)
    if (i1 == nullptr || i2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (i1->type != i2->type){
        return ERR_TYPE_MISMATCH;
    }

    KASMType t1, t2;
    t1 = i1->type;
    t2 = i2->type;

    if (t1==KT_INT && t2==KT_INT){res=Cmp<int, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_FLOAT){res=Cmp<int, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_CHAR){res=Cmp<int, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_INT && t2==KT_BYTE){res=Cmp<int, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_FLOAT && t2==KT_INT){res=Cmp<float, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_FLOAT){res=Cmp<float, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_CHAR){res=Cmp<float, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_FLOAT && t2==KT_BYTE){res=Cmp<float, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_CHAR && t2==KT_INT){res=Cmp<char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_FLOAT){res=Cmp<char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_CHAR){res=Cmp<char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_CHAR && t2==KT_BYTE){res=Cmp<char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1==KT_BYTE && t2==KT_INT){res=Cmp<unsigned char, int>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_FLOAT){res=Cmp<unsigned char, float>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_CHAR){res=Cmp<unsigned char, char>(i1->data, i2->data, t1, t2);}
    else if (t1==KT_BYTE && t2==KT_BYTE){res=Cmp<unsigned char, unsigned char>(i1->data, i2->data, t1, t2);}

    else if (t1 == KT_STRING && t2 == KT_STRING){ 
        res = (*(string*)i2->data).compare(*((string*)i1->data));
    }

    else {return ERR_ILLEGAL_ARG;}

    *(int*)reg->data = res;

    return ERR_OK;
}

//control
ErrCode _jmp (Instruction*inst, InstructionFrame*frame){
    
    if (inst->Rv0 == nullptr){
        return ERR_MISSING_ARG;
    } else if (inst->Rv0->type != KT_REF){
        return ERR_TYPE_MISMATCH;
    }
    
    frame->SetInstPntr((Instruction*)inst->Rv0->data);

    return ERR_OK;
}

ErrCode _jlss (Instruction*inst, InstructionFrame*frame){
   
    MemItem * reg = frame->GetRegisters()->GetRegister("cmr");
    if (*(int*)reg->data < 0){
        return _jmp(inst, frame);
    }

    return ERR_OK;
}

ErrCode _jgtr (Instruction*inst, InstructionFrame*frame){
    
    MemItem * reg = frame->GetRegisters()->GetRegister("cmr");
    if (*(int*)reg->data > 0){
        return _jmp(inst, frame);
    }

    return ERR_OK;
}

ErrCode _jeql (Instruction*inst, InstructionFrame*frame){
    
    MemItem * reg = frame->GetRegisters()->GetRegister("cmr");
    if (*(int*)reg->data == 0){
        return _jmp(inst, frame);
    }

    return ERR_OK;
}

ErrCode _jneql (Instruction*inst, InstructionFrame*frame){

    MemItem * reg = frame->GetRegisters()->GetRegister("cmr");
    if (*(int*)reg->data != 0){
        return _jmp(inst, frame);
    }

    return ERR_OK;
}

ErrCode _call (Instruction*inst, InstructionFrame*frame){

    if (inst->Rv0 == nullptr){
        return ERR_MISSING_ARG;
    } else if (inst->Rv0->type != KT_REF){
        return ERR_TYPE_MISMATCH;
    }
    
    frame->AddCallFrame();
    frame->SetInstPntr((Instruction*)inst->Rv0->data);

    return ERR_OK;

}

ErrCode _ret (Instruction*inst, InstructionFrame*frame){
    
    if (inst->Rv0 == nullptr){

    } else if (inst->Rv0->type == KT_INT){
        MemItem * mi = frame->GetRegisters()->GetRegister("rir");
        *(int*)mi->data = *((int*)inst->Rv0->data);
    } else if (inst->Rv0->type == KT_FLOAT){
        MemItem * mi = frame->GetRegisters()->GetRegister("rfr");
        *(float*)mi->data = *((float*)inst->Rv0->data);
    } else if (inst->Rv0->type == KT_CHAR){
        MemItem * mi = frame->GetRegisters()->GetRegister("rfr");
        *(char*)mi->data = *((char*)inst->Rv0->data);
    } else if (inst->Rv0->type == KT_BYTE){
        MemItem * mi = frame->GetRegisters()->GetRegister("rfr");
        *(unsigned char*)mi->data = *((unsigned char*)inst->Rv0->data);
    }
    
    frame->PopCallFrame();
    return ERR_OK;
}

//stack
ErrCode _push (Instruction*inst, InstructionFrame*frame){
    
    if (inst->Rv0 == nullptr) { return ERR_MISSING_ARG;}

    frame->GetCallFrame()->Push(
        inst->Rv0->type,
        inst->Rv0->data,
        inst->Rv0->isConst
    );
    
    return ERR_OK;
}

ErrCode _pop (Instruction*inst, InstructionFrame*frame){
    
    if (inst->Rv0 == nullptr) {return ERR_MISSING_ARG;}
    else if (inst->Rv0->isConst){return ERR_ILLEGAL_ARG;}
    CallFrame * cf = frame->GetCallFrame();
    if (cf == nullptr || cf->Stack.size() == 0) {return ERR_EMPTY_STACK;}

    MemItem * mi = cf->Pop();
    inst->Rv0 = mi;

    return ERR_OK;
}

//High level

ErrCode _getl (Instruction*inst, InstructionFrame*frame){

    if (inst->Rv0 == nullptr){
        return ERR_MISSING_ARG;
    } else if (inst->Rv0->type != KT_STRING){
        return ERR_TYPE_MISMATCH;
    }

    string tmp;
    getline(cin, tmp);
    *(string*)inst->Rv0->data = tmp;

    return ERR_OK;
}

ErrCode _prnt (Instruction*inst, InstructionFrame*frame){

    //TODO - replace with crossplat UI calls
    switch(inst->Rv0->type){
        case KT_INT:
        cout << *(int*)inst->Rv0->data;
        break;
        case KT_FLOAT:
        cout << *(float*)inst->Rv0->data;
        break;
        case KT_CHAR:
        cout << *(signed char*)inst->Rv0->data;
        break;
        case KT_BYTE:
        cout << *(unsigned char*)inst->Rv0->data;
        break;
        case KT_STRING:
        cout << *(string*)inst->Rv0->data;
        break;
        default:
        return ERR_TYPE_MISMATCH;
        break;
    }

    return ERR_OK;
}

ErrCode _goxy (Instruction*inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

ErrCode _clr (Instruction*inst, InstructionFrame*frame){
    return ERR_UNIMPLEMENTED;
}

//default instructions
void KASM::InitInstructionPntrs(InstructionRegistry* reg){
    reg->RegisterInstruction("noop", _noOp);
    reg->RegisterInstruction(":", _label);

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
    reg->RegisterInstruction("ret", _ret);

    reg->RegisterInstruction("push", _push);
    reg->RegisterInstruction("pop", _pop);

    reg->RegisterInstruction("getl", _getl);
    reg->RegisterInstruction("prnt", _prnt);
    reg->RegisterInstruction("goxy", _goxy);
    reg->RegisterInstruction("clr", _clr);


}