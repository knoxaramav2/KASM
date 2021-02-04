#include "debug.hpp"

#include <sstream>
#include <iostream>

using namespace std;

void Debug::WriteErr(int line, string& text, string& msg){
    Debug::WriteErr(line, text, msg.c_str());
}

void Debug::WriteErr(int line, string& text, const char* msg){
    ostringstream ss;
    ss << "Line (" << line << ") \""<<text.c_str()<<"\". " << msg;
    cout << ss.str() << endl;
}