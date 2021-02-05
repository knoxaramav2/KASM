#include "debug.hpp"

#include <sstream>
#include <iostream>

using namespace std;
using namespace KASM;

void Debug::WriteErr(int line, string&src, string& text, string& msg){
    Debug::WriteErr(line, src, text, msg.c_str());
}

void Debug::WriteErr(int line, std::string&src, string& text, const char* msg){
    
    size_t dirszf = src.find_last_of('/');
    size_t dirszb = src.find_last_of('\\');    
    size_t cutoff = dirszf == string::npos ? 0 : dirszf;

    if (dirszb != string::npos && dirszb > cutoff) { cutoff = dirszb; }

    string shortName = src.substr(cutoff+1, src.size());

    ostringstream ss;
    ss << shortName.c_str() << ":" << line << " \""<<text.c_str()<<"\". " << msg;
    cout << ss.str() << endl;
}