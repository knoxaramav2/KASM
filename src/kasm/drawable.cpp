#include <string>

#include "drawable.hpp"
#include "utils.hpp"
#include "controller.hpp"
#include "crossplat.hpp"
#include "limits.h"
#include "ncurses.h"

using namespace std;
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
ErrCode CheckArgsType(Instruction*inst, KASMType type, unsigned argNums){

    for(unsigned i = 0; i < argNums; ++i){
        
        MemItem * mi = nullptr;

        if (i == 0){ mi = inst->Rv0; }
        else if (i == 1){ mi = inst->Rv1; }
        else if (i == 2){ mi = inst->Rv2; }

        if (mi == nullptr){
            return ERR_MISSING_ARG;
        } else if (mi->type != type){
            return ERR_ILLEGAL_ARG;
        }
    }

    return ERR_OK;
}

//Check for null data?
ErrCode CheckArgInfo(MemItem*mi, KASMType type){

    if (mi == nullptr){ return ErrCode::ERR_MISSING_ARG; }
    if (mi->type != type){ return ErrCode::ERR_ILLEGAL_ARG; }

    return ErrCode::ERR_OK;
}

//Registered methods
ErrCode PushWindow(Instruction* inst, InstructionFrame* frame){



    return ERR_OK;
}

ErrCode SetXY(Instruction* inst, InstructionFrame* frame){

    ErrCode err = CheckArgsType(inst, KASMType::KT_INT, 2);

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

    ErrCode err = CheckArgsType(inst, KASMType::KT_INT, 2);

    if (err != ERR_OK) { return err; }

    if (inst->Rv2 == nullptr){
        return ERR_MISSING_ARG;
    } else if (inst->Rv2->type < KT_INT || inst->Rv2->type > KT_STRING){
        return ERR_ILLEGAL_ARG;
    }

    int x = *(int *)inst->Rv0->data;
    int y = *(int *)inst->Rv1->data;
    void * val = inst->Rv2->data;
    string r2;

    switch(inst->Rv2->type){
        case KASMType::KT_BYTE:
            r2 = string(1, *(unsigned char*) val);
        break;
        case KASMType::KT_CHAR:
            r2 = string(1, *(char*) val);
        break;
        case KASMType::KT_INT:
            r2 = to_string(*(int*) val);
        break;
        case KASMType::KT_FLOAT:
            r2 = to_string(*(float*) val);
            r2 = r2.erase(r2.find_last_not_of('0')+1, std::string::npos);
        break;
        case KASMType::KT_STRING:
            r2 = *(string*) val;
        break;
        default: return ErrCode::ERR_ILLEGAL_ARG;
    }

    if (!KCompat::Graphics::PlotXY(x, y, r2)){
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

ErrCode GetTerminalAttribute(Instruction* inst, InstructionFrame* frame){

    ErrCode err = ErrCode::ERR_OK;
    KCompat::Graphics::TerminalWH ta;
    KCompat::Graphics::TerminalXY pa;
    int val = 0;

    err = CheckArgInfo(inst->Rv0, KASMType::KT_CHAR);
    if (err) { return err; }

    err = CheckArgInfo(inst->Rv1, KASMType::KT_INT);
    if (err) { return err; }

    char attrChar = KASM::Utils::ToLower(*(char*) inst->Rv0->data);
    
    switch(attrChar){
        case 'x': pa = KCompat::Graphics::TerminalXY::XPOS; break;
        case 'y': pa = KCompat::Graphics::TerminalXY::YPOS; break;
        case 'w': ta = KCompat::Graphics::TerminalWH::WIDTH; break;
        case 'h': ta = KCompat::Graphics::TerminalWH::HEIGHT; break;
        default: return ErrCode::ERR_ILLEGAL_ARG;
    }

    if (attrChar == 'x' || attrChar == 'y'){
        val = KCompat::Graphics::GetCursorXY(pa);
    } else {
        val = KCompat::Graphics::GetTerminalAttribute(ta);
    }
    
    if (val == INT_MIN) { return ErrCode::ERR_OUT_OF_RANGE; }

    *(int*) inst->Rv1->data = val;
    return ErrCode::ERR_OK;
}

void StartCurses(){
    initscr();
    keypad(stdscr, TRUE);
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
    ctrl.RegisterCommand("gettrmattr", &GetTerminalAttribute);

}