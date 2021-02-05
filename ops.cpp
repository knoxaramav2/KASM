#include "ops.hpp"
#include "debug.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace KASM;

enum CharIndic{
    //Skip line
    NWS_None,       //(all ws)
    NWS_Comment,    //#  

    //Identifiers
    NWS_Constant,   //.
    NWS_Label,      //:

    //Special
    NWS_PreProc,    //$

    //general
    NWS_ID,         //aA-zZ
    NWS_ILLEGAL     //all else

};

CharIndic FirstNWSChar(string&s){
    for(size_t i = 0; i < s.size(); ++i){
        char c = s[i];

        if (IsWS(c)) { continue; }
        if (IsAlpha(c)) { return NWS_ID; }

        switch(c){
            case '#': return NWS_Comment;
            case '.': return NWS_Constant;
            case ':': return NWS_Label;
            case '$': return NWS_PreProc;
            default: return NWS_ILLEGAL;
        }
    }

    return NWS_None;
}


FileRaw::FileRaw(string filePath){

    cout << "Loading: " << filePath << endl;

    ifstream file;
    file.open(filePath.c_str(), ios::in);

    if (!file){
        cout << "File " << filePath << " not found" << endl; 
    }

    fileName = filePath;

    string line;
    while(getline(file, line)){
        cout << "> " << line << endl;
        lines.push_back(line);
    }

    cout << endl;

    file.close();
}


Instruction::Instruction(){
    Source = nullptr;
    Rv0 = Rv1 = Rv2 = nullptr;
}


InstructionFrame::InstructionFrame(KAsmRegisters&reg){
    _reg = &reg;
}

int InstructionFrame::GetLabel(string& line, int lineNo, FileRaw& raw){
    return 0;
    vector<string> terms = Utils::SplitString(line);

    if (terms.size() != 1) { return 1; }
    if (_labelTable.AddLabel(terms[0], raw, lineNo)) { return 2;}

    return 0;
}

void InstructionFrame::GetInstruction(string& line){
    vector<string> terms = Utils::SplitString(line);
}

void InstructionFrame::ProcessPreProc(string& line){
    return;
    //cout << "@ PREPROC: " << line << endl;
    vector<string> terms = Utils::SplitString(line);
}

void InstructionFrame::ProcessInlined(string& line){
    return;
    //cout << "@ INLINED: " << line << endl;
    vector<string> terms = Utils::SplitString(line);
}

void InstructionFrame::ProcessScripts(FileRaw&raw){
    for(size_t i = 0; i < raw.lines.size(); ++i){
        string str = raw.lines[i];
        CharIndic ci = FirstNWSChar(str);

        switch(ci){
            case NWS_None:
            case NWS_Comment:
            //Skip
            break;
            case NWS_Constant://add constant decl to current call frame
                Debug::WriteErr(i, raw.fileName, str, "Constants not yet implemented.");
            break;
            case NWS_Label://add to label table
            {
                int res = GetLabel(str, i, raw);
                if (res == 1) {
                    Debug::WriteErr(i, raw.fileName, str, "Illegal label declaration.");
                }
            }
            break;
            case NWS_PreProc://switch to preproc
                ProcessPreProc(str);
            break;
            case NWS_ID://instruction
                GetInstruction(str);
            break;
            case NWS_ILLEGAL://abort, throw error
                Debug::WriteErr(i, raw.fileName, str, "Illegal character");
            break;
        }
    }
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

    //_instructions.push_back(inst);
}

CallFrame * InstructionFrame::GetCallFrame(){
    if (_frameStack.size()==0) {return nullptr;}
    return &_frameStack[_frameStack.size()-1];
}

KAsmRegisters * InstructionFrame::GetRegisters(){
    return _reg;
}

void InstructionFrame::Test(){

    cout << "START TEST:" <<endl;

    InstructionProc proc = _instructions.GetInstruction("mov");
    Instruction* inst = new Instruction();
    inst->OpCode = KT_MOV;
    inst->Rv0 = new MemItem();
    inst->Rv1 = new MemItem();
    inst->Rv0->type=KT_INT;
    inst->Rv0->data=(void*) new int(3);
    inst->Rv0->isConst = true;
    inst->Rv1->data=(void*) _reg->GetRegister(KT_RI0);
    inst->Rv1->type=KT_INT;
    inst->Rv1->isConst=false;
    proc(*inst, this);

    InstructionProc prnt = _instructions.GetInstruction("prnt");
    Instruction* inst2 = new Instruction();
    inst2->OpCode = KT_PRINT;
    inst2->Rv0 = new MemItem();
    inst2->Rv0->type=KT_INT;
    inst2->Rv0->data=(void*) _reg->GetRegister(KT_RI0);
    inst2->Rv0->isConst = false;
    prnt(*inst2, this);

    cout << endl << "END TEST:" << endl;
}


bool LabelTable::AddLabel(string name, FileRaw&raw, int instNo){

    Label label;
    label.Name = name;
    label.LineNo = instNo;
    label.SourceFile = raw.fileName;

    if (_labels.find(name) == _labels.end()){
        _labels[name]=label;
    } else {
        Debug::WriteErr(instNo, raw.fileName, raw.lines[instNo], "Duplicate label.");
        return false;
    }
    
    return true;
}