#include <string>

#include "mem.hpp"
#include "utils.hpp"

using namespace std;
using namespace KASM;

/*
KAsmRegisters::KAsmRegisters(){
    for (size_t i = 0; i < KT_REG_CAP; ++i){
        
        MemItem * item = new MemItem();

        switch (i)
        {
        case KT_RI0:
        case KT_RI1:
        case KT_RI2:
        case KT_RI3:
        case KT_RI4:
        case KT_RI5:
        case KT_RI6:
        case KT_RI7:
            item->type = KT_INT;
            item->data = new int(0);
        break;

        case KT_RF0:
        case KT_RF1:
        case KT_RF2:
        case KT_RF3:
        case KT_RF4:
        case KT_RF5:
        case KT_RF6:
        case KT_RF7:
            item->type = KT_FLOAT;
            item->data = new float(0.0f);
        break;

        case KT_RB0:
        case KT_RB1:
        case KT_RB2:
        case KT_RB3:
        case KT_RB4:
        case KT_RB5:
        case KT_RB6:
        case KT_RB7:
            item->type = KT_BYTE;
            item->data = new unsigned char(0);
        break;

        case KT_RS0:
        case KT_RS1:
        case KT_RS2:
        case KT_RS3:
            item->type = KT_STRING;
            item->data = new string;
        break;

        case KT_RAC:
        case KT_RIR:
            item->type = KT_INT;
            item->data = new int(0);
        break;
        case KT_RFR:
            item->type = KT_FLOAT;
            item->data = new float(0.0f);
        break;
        case KT_RBR:
            item->type = KT_BYTE;
            item->data = new unsigned char(0);
        break;
        case KT_CTR:
            item->type = KT_INT;
            item->data = new int(0);
        break;
        case KT_REG_CAP: break;
        }

        _registers[i] = item;
    }
}
*/

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