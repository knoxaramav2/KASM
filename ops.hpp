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
        KT_LABEL,   //(meta)
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

    struct Instruction{
        FileRaw * Source;
        KASMOp OpCode;
        MemItem * Rv0;
        MemItem * Rv1;
        MemItem * Rv2;

        Instruction* Next;
        InstructionProc Proc;

        Instruction();
    };


    struct Label{
        Instruction* Inst;
        std::string Name;
        std::string SourceFile;
        int LineNo;
    };

    class LabelTable{

        std::map<std::string, Label> _labels;

        public:

        Instruction* AddLabel(std::string name, FileRaw&raw, int instNo, InstructionProc proc);
        Instruction* FindLabel(std::string name);

    };


    class InstructionFrame{
        friend struct Instruction;

        Instruction * _base;
        Instruction * _instPntr;

        //state
        int _runState=0;//0=not start, 1=running, 2=paused, 3=complete, -1=crash
        bool _scriptLoad = false;
        unsigned _scriptLevel = 0;


        //runtime
        std::vector<CallFrame> _frameStack;
        KAsmRegisters * _reg;
        InstructionRegistry _instructions;

        //compiletime
        LabelTable _labelTable;
        
        bool ParseArguments(Instruction* inst, std::vector<std::string>&args);
        bool Resolve();

        int GetLabel(std::string& line, int lineNp, FileRaw&raw);
        void GetInstruction(std::string& line, FileRaw&raw);
        
        void ProcessPreProc(std::string& line);
        void ProcessInlined(std::string& line);

        public:

        void ProcessScripts(FileRaw&raw);
        InstructionFrame(KAsmRegisters&reg);
        void AddInstruction(Instruction*inst);

        CallFrame * GetCallFrame();
        KAsmRegisters * GetRegisters();
        InstructionProc GetInstProc(std::string proc);

        bool Ready();
        void SetExit();

        //Control steps
        void Next();

        //#ifdef __DEBUG
        void Test();
        //#endif
    };
}

#endif