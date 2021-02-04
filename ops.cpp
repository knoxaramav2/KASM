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
    Source = nullptr;
    Rv0 = Rv1 = Rv2 = nullptr;
}


InstructionFrame::InstructionFrame(KAsmRegisters&reg){
    _reg = &reg;
}

void InstructionFrame::AddInstruction(
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


int LabelTable::ResolveInstructions(InstructionFrame &ctrl){

    int errors = 0;


    return errors;
}

bool LabelTable::AddLabel(std::string name, int instNo){

    Label label;
    label.Name = name;
    label.LineNo = instNo;
    
    return true;
}