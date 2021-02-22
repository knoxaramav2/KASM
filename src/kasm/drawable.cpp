#include "drawable.hpp"
#include "controller.hpp"

KASM::ErrCode PushWindow(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}


void KASM::GRAPHICS::InitGraphics(KASM::AsmController&ctrl){
    ctrl.RegisterCommand("pushxwin", &PushWindow);
}