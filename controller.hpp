#ifndef KASM_CTRL
#define KASM_CTRL

#include "ops.hpp"
#include <string>

namespace KASM{
    class AsmController{

        KAsmRegisters _reg;
        InstructionFrame _instFrame;

        public:

        AsmController();
        ~AsmController();

        void LoadScript(std::string path);
        bool RegisterCommand();
        bool Run();

        void PauseExecution();
        void ContinueExecution();
        void EndExecution();
    };
}



#endif
