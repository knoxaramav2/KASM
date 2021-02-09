#ifndef KASM_DBG
#define KASM_DBG

#include <string>

namespace KASM{
    class Debug{

        public:
        
        static void WriteErr(int line, std::string&src, std::string& text, std::string& msg);
        static void WriteErr(int line, std::string&src, std::string& text, const char* msg);
    
    };
}


#endif