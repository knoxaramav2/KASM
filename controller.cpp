#include "controller.hpp"

#include <iostream>

using namespace std;

KASMController::KASMController(){

}

KASMController::~KASMController(){

}

void KASMController::LoadScript(string path){
    cout << "Loading " << path << endl;
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