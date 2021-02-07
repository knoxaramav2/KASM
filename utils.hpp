#ifndef KASM_UTIL
#define KASM_UTIL

#include <string>
#include <vector>

#define IsWS(c) (c==' ' || c=='\t' || c=='\r' || c=='\n')
#define IsAlpha(c) ((c>='a' && c<='z') || (c>='A' && c<'Z') || c=='_')
#define IsNum(c) (c>='0' && c<='9')

namespace KASM{
    class Utils{

        public:

        //string
        static std::vector<std::string> SplitString(std::string line);
        static std::string ToUpper(std::string&);
        static std::string ToUpper(const char[]);
        static std::string ToLower(std::string&);
        static std::string ToLower(const char[]);
    };
}



#endif