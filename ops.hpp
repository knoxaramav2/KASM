#pragma once
#ifndef KASM_OPS
#define KASM_OPS

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "instructionRegistery.hpp"
#include "mem.hpp"

namespace KASM{
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
        KT_Call,    //call

        //Stack
        KT_PUSH,    //push
        KT_POP,     //pop

        //High level
        KT_PRINT,   //prnt
        KT_GOXY,    //goxy
        KT_CLRSCRN, //clr

        //End
        KT_END      //End of default instructions

    };

    struct FileRaw{
        std::string fileName;
        std::vector<std::string> lines;

        FileRaw(std::string filePath);
    };

    struct Label{
        std::string Name;
        std::string SourceFile;
        int LineNo;
    };

    class LabelTable{

        std::map<std::string, Label> _labels;

        public:

        bool AddLabel(std::string name, FileRaw&raw, int instNo);
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
        friend struct Instruction;
        //runtime
        std::vector<CallFrame> _frameStack;
        KAsmRegisters * _reg;
        InstructionRegistry _instructions;

        //compiletime
        LabelTable _labelTable;
        
        int GetLabel(std::string& line, int lineNp, FileRaw&raw);
        void GetInstruction(std::string& line);
        
        void ProcessPreProc(std::string& line);
        void ProcessInlined(std::string& line);

        public:

        void ProcessScripts(FileRaw&raw);
        InstructionFrame(KAsmRegisters&reg);
        void AddInstruction(
            FileRaw&src, KASMOp op, 
            MemItem * r0,
            MemItem * r1,
            MemItem * r2);

        CallFrame * GetCallFrame();
        KAsmRegisters * GetRegisters();

        //#ifdef __DEBUG
        void Test();
        //#endif
    };
}

#endif