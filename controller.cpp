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

    return true;
}

void AsmController::PauseExecution(){

}

void AsmController::ContinueExecution(){

}

void AsmController::EndExecution(){

}

void AsmController::Test(){
    _instFrame.Test();
}