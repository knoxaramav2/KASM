#pragma once
#ifndef KASM_PROCREG
#define KASM_PROCREG

#include "procdefs.hpp"

#include <map>
#include <string>

namespace KASM{
    class InstructionRegistry{

        std::map<std::string, InstructionProc> _instructions;

        void LoadDefaultInstructions();

        public:

        InstructionRegistry();
        ~InstructionRegistry();

        bool RegisterInstruction(std::string name, InstructionProc proc);
        InstructionProc GetInstruction(std::string inst);
    };
}

#endif