#include "drawable.hpp"

KASM::ErrCode PushWindow(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}


void KASM::InitGraphics(){
    _pushWindow = &PushWindow;
}