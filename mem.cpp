#include "mem.hpp"

using namespace std;

MemItem::MemItem(){
    type = KT_INT;
    data = nullptr;
    isConst = true;
}

MemItem::~MemItem(){

}