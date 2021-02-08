#include <string>

#include "mem.hpp"
#include "utils.hpp"

using namespace std;
using namespace KASM;

KAsmRegisters::KAsmRegisters(){
    LoadRegisters();
}

KAsmRegisters::~KAsmRegisters(){

}

void KAsmRegisters::LoadRegisters(){
    _registers["ri0"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri1"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri2"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri3"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri4"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri5"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri6"] = new MemItem(KT_INT, false, new int(0));
    _registers["ri7"] = new MemItem(KT_INT, false, new int(0));

    _registers["rf0"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf1"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf2"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf3"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf4"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf5"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf6"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rf7"] = new MemItem(KT_FLOAT, false, new float(0.0f));

    _registers["rb0"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb1"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb2"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb3"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb4"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb5"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb6"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["rb7"] = new MemItem(KT_BYTE, false, new char(0));

    _registers["rs0"] = new MemItem(KT_STRING, false, new string);
    _registers["rs1"] = new MemItem(KT_STRING, false, new string);
    _registers["rs2"] = new MemItem(KT_STRING, false, new string);
    _registers["rs3"] = new MemItem(KT_STRING, false, new string);

    _registers["rac"] = new MemItem(KT_INT, false, new int(0));
    _registers["rir"] = new MemItem(KT_INT, false, new int(0));
    _registers["rfr"] = new MemItem(KT_FLOAT, false, new float(0.0f));
    _registers["rbr"] = new MemItem(KT_BYTE, false, new char(0));
    _registers["ctr"] = new MemItem(KT_INT, false, new int(0));
    _registers["cmr"] = new MemItem(KT_INT, false, new int(0));
}

void * KAsmRegisters::GetValue(string& reg){
    if (_registers.find(reg) == _registers.end()) {return nullptr;}
    return _registers[reg]->data;
}

bool KAsmRegisters::SetValue(string& reg, void * data){
    if (_registers.find(reg) == _registers.end()) {return false;}
    _registers[reg]->data = data;
    return true;
}

MemItem * KAsmRegisters::GetRegister(string& reg){
    string lwr = Utils::ToLower(reg);
    if (_registers.find(lwr) == _registers.end()) {return nullptr;}
    return _registers[lwr];
}

MemItem * KAsmRegisters::GetRegister(const char reg[]){
    string str(reg);
    return GetRegister(str);
}

MemItem::MemItem(){
    type = KT_INT;
    data = nullptr;
    isConst = true;
}

MemItem::MemItem(KASMType type, bool isConst, void*data){
    this->type = type;
    this->isConst = isConst;
    this->data = data;
}

MemItem::~MemItem(){

}


CallFrame::CallFrame(){
    Callee = nullptr;
}

CallFrame::~CallFrame(){

}




