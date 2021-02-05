#include "instructionRegistery.hpp"
#include "defaultInstructions.hpp"

#include <iostream>

using namespace std;
using namespace KASM;

InstructionRegistry::InstructionRegistry(){
    LoadDefaultInstructions();
}

InstructionRegistry::~InstructionRegistry(){

}

void InstructionRegistry::LoadDefaultInstructions(){
    InitInstructionPntrs(this);
}

bool InstructionRegistry::RegisterInstruction(string fncName, InstructionProc proc){
    
    if (_instructions.find(fncName) != _instructions.end()){
        return false; //Function/label name already exists
    }
    
    _instructions[fncName] = proc;
    return true;
}

InstructionProc InstructionRegistry::GetInstruction(string inst){
    if (_instructions.find(inst) == _instructions.end()){
        return nullptr;
    }

    return _instructions[inst];
}