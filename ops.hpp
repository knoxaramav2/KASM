#ifndef KASM_OPS
#define KASM_OPS

#include <string>
#include <vector>

#include "mem.hpp"

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
    KT_PSTK     //

};

struct FileRaw{
    std::string fileName;
    std::vector<std::string> lines;

    FileRaw(std::string filePath);
};

struct Instruction{
    FileRaw * Source;
    KASMOp OpCode;
    MemItem * Rv0;
    MemItem * Rv1;
    MemItem * Rv2;

    Instruction();
};

class InstructionFrame{

    CallFrame _stackFrame;
    std::vector<Instruction> _instructions;
    KAsmRegisters * _reg;

    public:

    InstructionFrame(KAsmRegisters&reg);
    void AddInstruction(
        FileRaw&src, KASMOp op, 
        MemItem * r0,
        MemItem * r1,
        MemItem * r2);
};

struct Label{
    std::string Name;
    int LineNo;
};

class LabelTable{

    std::vector<Label> _labels;

    public:

    int ResolveInstructions(InstructionFrame &ctrl);
    bool AddLabel(std::string name, int instNo);
};

#endif