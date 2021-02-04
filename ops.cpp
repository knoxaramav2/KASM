#include "ops.hpp"
#include "debug.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#define IsWS(c) (c==' ' || c=='\t' || c=='\r' || c=='\n')
#define IsAlpha(c) ((c>='a' && c<='z') || (c>='A' && c<'Z') || c=='_')
#define IsNum(c) (c>='0' && c<='9')

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
            case ':': return NWS_Constant;
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
                Debug::WriteErr(i, str, "Constants not yet implemented");
            break;
            case NWS_Label://add to label table
                
            break;
            case NWS_PreProc://switch to preproc

            break;
            case NWS_ID://instruction

            break;
            case NWS_ILLEGAL://abort, throw error

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

    _instructions.push_back(inst);
}

bool LabelTable::AddLabel(std::string name, int instNo){

    Label label;
    label.Name = name;
    label.LineNo = instNo;
    
    return true;
}