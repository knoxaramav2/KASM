#include "drawable.hpp"
#include "controller.hpp"

KASM::ErrCode PushWindow(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode SetXY(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode SetColor(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode DrawRectagle(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode DrawCircle(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode PlotAt(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}

KASM::ErrCode MoveWindow(KASM::Instruction* inst, KASM::InstructionFrame* frame){



    return KASM::ERR_OK;
}




void KASM::GRAPHICS::InitGraphics(KASM::AsmController&ctrl){
    ctrl.RegisterCommand("pushxwin", &PushWindow);
    ctrl.RegisterCommand("setxy", &SetXY);
    ctrl.RegisterCommand("setclr", &SetColor);
    ctrl.RegisterCommand("rect", &DrawRectagle);
    ctrl.RegisterCommand("circ", &DrawCircle);
    ctrl.RegisterCommand("plotxy", &PlotAt);
    ctrl.RegisterCommand("mvwin", &MoveWindow);
}