#include "drawable.hpp"
#include "controller.hpp"
#include "crossplat.hpp"
#include "ncurses.h"

using namespace KASM;


//Drawable classes/methods

/*
    Renderable cell
    character: Printed character
    attr: binary flags for color, transparency
*/

struct TCell{
    char character;
    unsigned int attr;
};

class TWindow{

    unsigned _width, _height;
    unsigned _x, _y;

    public:

    TWindow();
    ~TWindow();

};

class WindowController{

    public:

};

WindowController _winCtrl;

void GRAPHICS::StartGlobals(){

}

//Helper methods
ErrCode CheckIntArgs(Instruction*inst, unsigned argNums){

    for(unsigned i = 0; i < argNums; ++i){
        
        MemItem * mi = nullptr;

        if (i == 0){ mi = inst->Rv0; }
        else if (i == 1){ mi = inst->Rv1; }
        else if (i == 2){ mi = inst->Rv2; }

        if (mi == nullptr){
            return ERR_MISSING_ARG;
        } else if (mi->type != KASMType::KT_INT){
            return ERR_ILLEGAL_ARG;
        }
    }

    return ERR_OK;
}



//Registered methods
ErrCode PushWindow(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode SetXY(Instruction* inst, InstructionFrame* frame){

    ErrCode err = CheckIntArgs(inst, 2);

    if (err != ERR_OK) { return err; }
    int x = *(int *)inst->Rv0->data;
    int y = *(int *)inst->Rv1->data;
    
    if (!KCompat::Graphics::SetCursorXY(x, y)){
        return ERR_OUT_OF_RANGE;
    }

    return ERR_OK;
}

ErrCode SetColor(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode DrawRectagle(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode DrawCircle(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode PlotAt(Instruction* inst, InstructionFrame* frame){

    ErrCode err = CheckIntArgs(inst, 2);

    if (err != ERR_OK) { return err; }

    if (inst->Rv2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (inst->Rv2->type != KT_CHAR || inst->Rv2->type != KT_BYTE){
        return ERR_ILLEGAL_ARG;
    }

    int x = *(int *)inst->Rv0->data;
    int y = *(int *)inst->Rv1->data;
    char c = *(char *)inst->Rv2->data;
    
    if (!KCompat::Graphics::PlotXY(x, y, c)){
        return ERR_OUT_OF_RANGE;
    }

    return ERR_OK;
}

ErrCode MoveWindow(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode SetTerminalSize(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}


void StartCurses(){

    initscr();

}

void GRAPHICS::InitGraphics(AsmController&ctrl){

    StartCurses();

    ctrl.RegisterCommand("pushxwin", &PushWindow);
    ctrl.RegisterCommand("setxy", &SetXY);
    ctrl.RegisterCommand("setclr", &SetColor);
    ctrl.RegisterCommand("rect", &DrawRectagle);
    ctrl.RegisterCommand("circ", &DrawCircle);
    ctrl.RegisterCommand("plotxy", &PlotAt);
    ctrl.RegisterCommand("mvwin", &MoveWindow);
    ctrl.RegisterCommand("settrmsz", &SetTerminalSize);
}