#ifndef KASM_CTRL
#define KASM_CTRL

#include "ops.hpp"

#include <string>

class KASMController{

    KAsmRegisters _reg;
    InstructionFrame _instFrame;

    public:

    KASMController();
    ~KASMController();

    void LoadScript(std::string path);
    bool RegisterCommand();
    bool Run();

    void PauseExecution();
    void ContinueExecution();
    void EndExecution();
};

#endif
