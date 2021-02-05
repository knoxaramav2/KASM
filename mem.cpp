#include "mem.hpp"

using namespace std;
using namespace KASM;

MemItem::MemItem(){
    type = KT_INT;
    data = nullptr;
    isConst = true;
}

MemItem::~MemItem(){

}