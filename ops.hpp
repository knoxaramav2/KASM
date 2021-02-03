#ifndef KASM_OPS
#define KASM_OPS

//Default Ops
enum KASMOp{
    KT_NONE,

    //General
    KT_MOV,     //mov
    KT_EXIT,    //exit    

    //Math
    KT_ADD,     //add
    KT_MULT,    //mult
    KT_DIV,     //div
    KT_POW,     //pow

    //Logic
    KT_CMP,     //cmp
    KT_JLSS,    //jl
    KT_JGTR,    //jg
    KT_JEQL,    //je
    KT_JNEQL,   //jne

    //Control
    KT_JMP,     //jmp

    //Stack
    KT_PUSH,    //push
    KT_POP,     //pop

};

#endif