#ifndef KASM_CTRL
#define KASM_CTRL

#include "ops.hpp"

#include <string>

class KASMController{

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
