#include "defaultInstructions.hpp"

#include <string>
#include <iostream>

using namespace std;
using namespace KASM;

int _noOp (Instruction&inst, InstructionFrame*frame){

    cout << "NOOP called" << endl;

    return 0;
}


//default instructions
void KASM::InitInstructionPntrs(InstructionRegistry* reg){
    reg->RegisterInstruction("noop", _noOp);
}