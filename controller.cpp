#include "controller.hpp"
#include "crossplat.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace KASM;

AsmController::AsmController() : _instFrame(_reg){

}

AsmController::~AsmController(){

}

void AsmController::LoadScript(string path){
    string relPath = KCompat::FormatPath(path);
    FileRaw fr(relPath);
    _instFrame.ProcessScripts(fr);
}

bool AsmController::RegisterCommand(InstructionProc proc){

    return true;
}

bool AsmController::Run(){

    if (!_instFrame.Ready()){
        return false;
    }

    _state = 1;

    while(_instFrame.Ready() && _state==1){
        _instFrame.Next();
    }

    return true;
}

void AsmController::PauseExecution(){
    _state = 2;
}

void AsmController::ContinueExecution(){
    if (_instFrame.Ready()){
        _state = 1;
    }
}

void AsmController::EndExecution(){
    _state = -1;
}

void AsmController::Test(){
    _instFrame.Test();
}