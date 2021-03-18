#ifndef KASM_CTRL
#define KASM_CTRL

#include "ops.hpp"

#include <string>

namespace KASM{
    class AsmController{

        KAsmRegisters _reg;
        InstructionFrame _instFrame;

        int _state = 0;

        public:

        AsmController();
        ~AsmController();

        bool LoadScript(std::string path);
        bool RegisterCommand(std::string name, InstructionProc proc);
        bool RegisterRegister(std::string name, size_t size);
        bool Run();

        void PauseExecution();
        void ContinueExecution();
        void EndExecution();

        void Test();
    };
}



#endif
