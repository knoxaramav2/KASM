#include "ops.hpp"

#include <fstream>

using namespace std;


FileRaw::FileRaw(string filePath){
    ifstream file;
    file.open(filePath.c_str(), ios::in);

    fileName = filePath;

    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }

    file.close();
}


Instruction::Instruction(){
    Source = NULL;
    Rv0 = Rv1 = Rv2 = NULL;
}


InstructionController::InstructionController(KAsmRegisters&reg){
    _reg = &reg;
}

void InstructionController::AddInstruciton(
    FileRaw&src, KASMOp op, 
    MemItem * r0,
    MemItem * r1,
    MemItem * r2
){
    Instruction inst;
    inst.OpCode = op;
    inst.Source = &src;
    inst.Rv0 = r0;
    inst.Rv1 = r1;
    inst.Rv2 = r2;

    _instructions.push_back(inst);
}