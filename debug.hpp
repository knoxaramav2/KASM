#ifndef KASM_DBG
#define KASM_DBG

#include <string>

class Debug{

    public:
    
    static void WriteErr(int line, std::string& text, std::string& msg);
    static void WriteErr(int line, std::string& text, const char* msg);
 
};


#endif