#include "ops.hpp"
#include "debug.hpp"
#include "utils.hpp"
#include "crossplat.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace KASM;

//Identifier for line type
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

    file.close();
}


Instruction::Instruction(){
    Source = nullptr;
    Rv0 = Rv1 = Rv2 = nullptr;
    Next = nullptr;
    Proc = nullptr;
}

Instruction::~Instruction(){
    
    //KASM::ClearMemItem(Rv0);
    //KASM::ClearMemItem(Rv1);
    //KASM::ClearMemItem(Rv2);
}

InstructionFrame::InstructionFrame(KAsmRegisters&reg){
    _reg = &reg;

    _base = _instPntr = nullptr;
}

MemItem * GrabValue(string&str, KAsmRegisters*reg){

    MemItem * ret = nullptr;

    if (Utils::IsNumeric(str)){
        ret = new MemItem();
        ret->type = KASMType::KT_INT;
        ret->isConst = true;
        ret->data = new int(0);
        *(int*)ret->data = atoi(str.c_str());
    } else {
        ret = reg->GetRegister(str);
    }

    return ret;
}

ErrCode GetStackAt(std::vector<MemItem>& _stackFrame, InstructionFrame * frame, string& arg){

    string substr = arg.substr(1, arg.length()-2);
    if (substr == "") {return ERR_MISSING_ARG;}

    string raw;
    vector<string> terms;
    size_t last = 0;

    //Parse offset terms
    for(size_t i=0; i <= substr.size(); ++i){
        if (substr[i] == '+' || substr[i] == '-' || substr[i] == 0){
            raw = substr.substr(last, i);
            terms.push_back(raw);
            last = i + 1;

            if (substr[i] == 0) {break;}

            terms.push_back(string(1, substr[i]));
            last = i+1;
        }
    }

    //Calculate offset
    bool add = 0;

    //Must have odd num of terms
    if (terms.size() % 2 == 0){
        return ERR_MISSING_ARG;
    }

    MemItem * tmp = nullptr;
    Instruction * inst = nullptr;

    MemItem * offreg = frame->GetRegisters()->GetRegister("off");
    tmp = GrabValue(terms[0], frame->GetRegisters());
    inst = new Instruction();
    inst->OpCode = KASMOp::KT_MOV;
    inst->Rv0 = tmp;
    inst->Rv1 = offreg;
    inst->Proc = frame->GetInstProc("mov");
    frame->AddInstruction(inst);

    for (size_t i = 1; i < terms.size(); ++i){
        string term = terms[i];
        if (i % 2 == 1){
            if (term == "+") {add = true;}
            else if (term == "-") {add = false;}
            else {
                //TODO throw error
            }


        } else {
            tmp = GrabValue(term, frame->GetRegisters());

            if (!add){
                *(int*)tmp->data = -*(int*)tmp->data;
            }

            inst = new Instruction();
            inst->OpCode = KT_ADD;
            inst->Rv0 = tmp;
            inst->Rv1 = offreg;
            inst->Proc = frame->GetInstProc("add");
            frame->AddInstruction(inst);
        }
    }

    //replace offset register value with value at stack offset
    inst = new Instruction();
    inst->OpCode = KT_GSA;
    inst->Rv0 = offreg;
    inst->Rv1 = offreg;
    inst->Proc = frame->GetInstProc("gsa");
    frame->AddInstruction(inst);

    return ERR_OK;
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
            item = _reg->GetRegister(str);
        } else if (IsNum(first)){//int,float
            if (str.find('.') != string::npos){
                item->data = new float(atof(str.c_str()));
                item->type = KT_FLOAT;
            } else {
                item->data = new int(atoi(str.c_str()));
                item->type = KT_INT;
            } 

            item->isConst = true;
        } else if (first==':'){
            item->isConst = true;
            item->type = KT_REF;
            _labelTable.AddTmpJmpInst(str, inst);
        } else if (first=='['){
            delete item;
            GetStackAt(_stackFrame, this, str);
            item = _reg->GetRegister("off");
        }

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

bool InstructionFrame::Resolve(){
    //Find start label, set instruction pointer
    Instruction* pntr = _labelTable.FindLabel(":start");
    if (pntr == nullptr) {return false;}
    _instPntr = pntr;

    //find label calls, associate with label fnc pointers
    _labelTable.ResolveTmp();
    AddCallFrame();
    _frameStack[0].Callee = nullptr;

    return true;
}

//Creates a dummy instruction for jumps
int InstructionFrame::GetLabel(string& line, int lineNo, FileRaw& raw){
    vector<string> terms = Utils::SplitString(line);
    Instruction* instPtr = nullptr;

    if (terms.size() != 1) { return 1; }
    if ((instPtr=_labelTable.AddLabel(terms[0], raw, lineNo, _instructions.GetInstruction(":"))) == nullptr) {
         return 2;
    } else {
        AddInstruction(instPtr);
    }

    return 0;
}

bool InstructionFrame::GetInstruction(string& line, FileRaw&src){
    vector<string> terms = Utils::SplitString(line);
    string com = terms[0];
    terms.erase(terms.begin());

    Instruction * inst = new Instruction();
    inst->Source = &src;
    inst->Proc = _instructions.GetInstruction(com);

    if (inst->Proc == nullptr){
        return false;
    }

    #ifdef __DEBUG
    inst->com = com;
    #endif

    ParseArguments(inst, terms);   
    AddInstruction(inst);

    return true;
}

void InstructionFrame::ProcessPreProc(string& line){
    vector<string> terms = Utils::SplitString(line);

    string directive = terms[0];
    terms.erase(terms.begin());

    if (directive == "$import"){
        if (terms.size() == 1){
            string path = KCompat::String::FormatPath(terms[0]);
            FileRaw fr(path);
            ProcessScripts(fr);
        } else {
            cout << "Import directive must have 1 argument." << endl;
            return;
        }
    } else {
        cout << "Directive not recognized: " << directive << endl;
        return;
    }
}

void InstructionFrame::ProcessInlined(string& line){
    return;
    //cout << "@ INLINED: " << line << endl;
    vector<string> terms = Utils::SplitString(line);
}

bool InstructionFrame::ProcessScripts(FileRaw&raw){
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
                if (!GetInstruction(str, raw)){
                    string errLn = "Command not found: ";
                    errLn += str;
                    Debug::WriteErr(i, raw.fileName, str, errLn);
                    _compileSuccess = false;
                    return false;
                }
            break;
            case NWS_ILLEGAL://abort, throw error
                Debug::WriteErr(i, raw.fileName, str, "Illegal character");
            break;
        }
    }

    --_scriptLevel;

    if (_scriptLevel==0){
        Resolve();
    }

    return true;
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

void InstructionFrame::AddCallFrame(){
    CallFrame cf;
    cf.Callee = _instPntr;
    _frameStack.push_back(cf);
}

void InstructionFrame::PopCallFrame(){
    CallFrame * cf = GetCallFrame();

    if (cf == nullptr) {return;}

    _instPntr = cf->Callee;
    _frameStack.pop_back();
}

KAsmRegisters * InstructionFrame::GetRegisters(){
    return _reg;
}

InstructionProc InstructionFrame::GetInstProc(string proc){
    return _instructions.GetInstruction(proc);
}

bool InstructionFrame::SetInstPntr(Instruction*inst){

    if (inst == nullptr) {return false;}

    _instPntr = inst;

    return true;
}

MemItem InstructionFrame::PopStack(){
    MemItem mi;

    if (_stackFrame.size() == 0){
        return mi;
    }

    mi = _stackFrame[_stackFrame.size()-1];
    _stackFrame.pop_back();
    return mi;
}

void InstructionFrame::PushStack(MemItem mi){
    _stackFrame.push_back(mi);
}

KASMType InstructionFrame::PeekStack(){
    if (_stackFrame.size() == 0) {return KT_NA;}
    return _stackFrame[_stackFrame.size()-1].type;
}

MemItem * InstructionFrame::StackFromTop(int idx){

    if (idx < 0 || (size_t) idx >= _stackFrame.size()){
        return nullptr;
    }

    return &_stackFrame[_stackFrame.size()-idx-1];
}

bool InstructionFrame::Ready(){
    return _scriptLevel==0 && _scriptLoad && _runState==0 && _compileSuccess;
}

void InstructionFrame::SetExit(){
    _runState = 3;
}

void InstructionFrame::Next(){
    if (!Ready()) { return; }

    #ifdef __DEBUG
    //cout << "> " << _instPntr->com << endl;
    #endif 

    ErrCode err = _instPntr->Proc(_instPntr, this);

    if (err != ERR_OK) {
        cout << "Err: " << err << endl;
        _runState = 3;
        return;
    }

    if (_instPntr == nullptr || _instPntr->Next == nullptr){
        _runState = -1;
        return;
    }

    _instPntr = _instPntr->Next;
}

void InstructionFrame::Test(){

    cout << "START TEST:" <<endl;
/*
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
*/
    cout << endl << "END TEST:" << endl;
}


Instruction* LabelTable::AddLabel(string name, FileRaw&raw, int instNo, InstructionProc proc){

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
    ret->Proc = proc;
    ret->OpCode = KT_LABEL;
    label.Inst = ret;
    _labels[name]=label;

    return ret;
}

Instruction* LabelTable::FindLabel(string name){

    if (_labels.find(name) == _labels.end()) {return nullptr;}
    return _labels[name].Inst;
}

void LabelTable::AddTmpJmpInst(string name, Instruction*inst){
    TmpLabel lbl;
    lbl.Name = name;
    lbl.Inst = inst;

    _tmp.push_back(lbl);
}

bool LabelTable::ResolveTmp(){

    for(size_t i=0; i < _tmp.size(); ++i){
        TmpLabel lbl = _tmp[i];
        
        if (_labels.find(lbl.Name) == _labels.end()){
            return false;
        }
        
        Label l = _labels[lbl.Name];
        lbl.Inst->Rv0->data = l.Inst;
        lbl.Inst->Rv0->type = KT_REF;
    }

    _tmp.clear();
    return true;
}