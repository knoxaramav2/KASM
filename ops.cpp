#include "ops.hpp"
#include "debug.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

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
    Next = nullptr;
    Proc = nullptr;
}


InstructionFrame::InstructionFrame(KAsmRegisters&reg){
    _reg = &reg;

    _base = _instPntr = nullptr;
}

bool InstructionFrame::ParseArguments(Instruction* inst, vector<string>& args){

    for(size_t i = 0; i < args.size(); ++i){
        string str = args[i];
        char first = str[0];
        char last = str[str.size()-1];

        MemItem * item = new MemItem();

        if (first == '\"'){//string
            if (last != '\"') {return false;}
            item->data = new string(str.begin()+1, str.end()-1);
            item->isConst=true;
            item->type=KT_STRING;
        } else if (first == '\'' ){//char
            if (str.length()!=3 || str[str.size()-1]!='\'') {return false;}
            item->data = new char(str[1]);
            item->isConst=true;
            item->type=KT_CHAR;
        } else if (IsAlpha(first)){//register
            
        } else if (IsNum(first)){//int,float
            if (str.find('.') == string::npos){
                item->data = new float(atof(str.c_str()));
                item->type = KT_FLOAT;
            } else {
                item->data = new int(atoi(str.c_str()));
                item->type = KT_INT;
            } 

            item->isConst = true;
        };

        if (inst->Rv0 == nullptr){
            inst->Rv0 = item;
        } else if (inst->Rv1 == nullptr){
            inst->Rv1 = item;
        } else if (inst->Rv2 == nullptr){
            inst->Rv2 = item;
        } else {
            return false;
        }
    }

    return true;
}

//Creates a dummy instruction for jumps
int InstructionFrame::GetLabel(string& line, int lineNo, FileRaw& raw){
    vector<string> terms = Utils::SplitString(line);
    Instruction* instPtr = nullptr;

    if (terms.size() != 1) { return 1; }
    if (_labelTable.AddLabel(terms[0], raw, lineNo) == nullptr) {
         return 2;
    } else {
        AddInstruction(instPtr);
    }

    return 0;
}

void InstructionFrame::GetInstruction(string& line, FileRaw&src){
    vector<string> terms = Utils::SplitString(line);
    string com = terms[0];
    terms.erase(terms.begin());

    Instruction * inst = new Instruction();
    inst->Source = &src;
    inst->Proc = _instructions.GetInstruction(com);
    ParseArguments(inst, terms);   
    AddInstruction(inst);
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
    _scriptLoad = true;
    ++_scriptLevel;

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
                if (res) {
                    Debug::WriteErr(i, raw.fileName, str, "Invalid label declaration.");
                }
            }
            break;
            case NWS_PreProc://switch to preproc
                ProcessPreProc(str);
            break;
            case NWS_ID://instruction
                GetInstruction(str, raw);
            break;
            case NWS_ILLEGAL://abort, throw error
                Debug::WriteErr(i, raw.fileName, str, "Illegal character");
            break;
        }
    }

    --_scriptLevel;
}

void InstructionFrame::AddInstruction(Instruction*inst){
    if (_base == nullptr){
        _base = inst;
        _instPntr = inst;
    } else {
        _instPntr->Next = inst;
        _instPntr=_instPntr->Next;
    }
}

CallFrame * InstructionFrame::GetCallFrame(){
    if (_frameStack.size()==0) {return nullptr;}
    return &_frameStack[_frameStack.size()-1];
}

KAsmRegisters * InstructionFrame::GetRegisters(){
    return _reg;
}

bool InstructionFrame::Ready(){
    return _scriptLevel==0 && _scriptLoad;
}

void InstructionFrame::Test(){

    cout << "START TEST:" <<endl;

    string r1 = "ri0";
    InstructionProc proc = _instructions.GetInstruction("mov");
    Instruction inst;
    inst.OpCode = KT_MOV;
    inst.Rv0 = new MemItem();
    inst.Rv1 = new MemItem();
    inst.Rv0->type=KT_INT;
    inst.Rv0->data=(void*) new int(3);
    inst.Rv0->isConst = true;
    inst.Rv1->data=(void*) _reg->GetRegister(r1);
    inst.Rv1->type=KT_INT;
    inst.Rv1->isConst=false;
    proc(inst, this);

    InstructionProc prnt = _instructions.GetInstruction("prnt");
    Instruction inst2;
    inst2.OpCode = KT_PRINT;
    inst2.Rv0 = new MemItem();
    inst2.Rv0->type=KT_INT;
    inst2.Rv0->data=(void*) _reg->GetRegister(r1);
    inst2.Rv0->isConst = false;
    prnt(inst2, this);

    cout << endl << "END TEST:" << endl;
}


Instruction* LabelTable::AddLabel(string name, FileRaw&raw, int instNo){

    Instruction* ret = nullptr;
    Label label;
    label.Name = name;
    label.LineNo = instNo;
    label.SourceFile = raw.fileName;

    if (_labels.find(name) != _labels.end()){
        Debug::WriteErr(instNo, raw.fileName, raw.lines[instNo], "Duplicate label.");
        return nullptr;
    }

    ret = new Instruction();
    ret->OpCode = KT_LABEL;
    label.Inst = ret;
    _labels[name]=label;
    
    return ret;
}