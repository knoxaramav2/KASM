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

        //Logic (check ops.cpp resolve, will check between jlss and jneql)
        KT_CMP,     //cmp
        KT_JLSS,    //jl
        KT_JGTR,    //jg
        KT_JEQL,    //je
        KT_JNEQL,   //jne

        //Control
        KT_JMP,     //jmp
        KT_Call,    //call
        KT_RET,     //ret

        //Stack
        KT_PUSH,    //push
        KT_POP,     //pop

        //High level
        KT_GETL,    //getl
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

        #ifdef __DEBUG
        std::string com;
        #endif

        FileRaw * Source;
        KASMOp OpCode;
        MemItem * Rv0;
        MemItem * Rv1;
        MemItem * Rv2;

        Instruction* Next;
        InstructionProc Proc;

        Instruction();
        ~Instruction();
    };


    struct Label{
        Instruction* Inst;
        std::string Name;
        std::string SourceFile;
        int LineNo;
    };


    class LabelTable{

        //placeholders for 
        //jmp instruction labels
        struct TmpLabel{
            std::string Name;
            Instruction*Inst;
        };

        std::map<std::string, Label> _labels;
        std::vector<TmpLabel> _tmp;  

        public:

        Instruction* AddLabel(std::string name, FileRaw&raw, int instNo, InstructionProc proc);
        Instruction* FindLabel(std::string name);

        void AddTmpJmpInst(std::string name, Instruction*inst);
        bool ResolveTmp();
    };


    class InstructionFrame{
        friend struct Instruction;
        friend class AsmController;

        Instruction * _base;
        Instruction * _instPntr;

        //state
        int _runState=0;//0=not start, 1=running, 2=paused, 3=complete, -1=crash
        bool _scriptLoad = false;
        unsigned _scriptLevel = 0;
        bool _compileSuccess = true;


        //runtime
        std::vector<CallFrame> _frameStack;//TODO
        std::vector<MemItem> _stackFrame;//Better names
        KAsmRegisters * _reg;
        InstructionRegistry _instructions;

        //compiletime
        LabelTable _labelTable;
        
        bool ParseArguments(Instruction* inst, std::vector<std::string>&args);
        bool Resolve();

        int GetLabel(std::string& line, int lineNp, FileRaw&raw);
        bool GetInstruction(std::string& line, FileRaw&raw);
        
        void ProcessPreProc(std::string& line);
        void ProcessInlined(std::string& line);

        public:

        bool ProcessScripts(FileRaw&raw);
        InstructionFrame(KAsmRegisters&reg);
        void AddInstruction(Instruction*inst);

        CallFrame * GetCallFrame();
        void AddCallFrame();
        void PopCallFrame();
        KAsmRegisters * GetRegisters();
        InstructionProc GetInstProc(std::string proc);
        bool SetInstPntr(Instruction*);

        MemItem PopStack();
        void PushStack(MemItem);
        KASMType PeekStack();

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