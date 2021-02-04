#include "controller.hpp"
#include "crossplat.hpp"

#include <iostream>
#include <fstream>

using namespace std;

KASMController::KASMController() : _instFrame(_reg){

}

KASMController::~KASMController(){

}

void KASMController::LoadScript(string path){
    string relPath = KCompat::FormatPath(path);
    FileRaw fr(relPath);
    _instFrame.ProcessScripts(fr);
}

bool KASMController::RegisterCommand(){

    return true;
}

bool KASMController::Run(){

    return true;
}

void KASMController::PauseExecution(){

}

void KASMController::ContinueExecution(){

}

void KASMController::EndExecution(){

}