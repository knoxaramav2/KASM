#ifndef KASM_CROSS
#define KASM_CROSS

#include <string>

#ifdef __WINDOWS
    #error Windows support not implemented yet
    //#define EL "\r\n"
#else
    #define EL "\n"
#endif

namespace KASM{
    class KCompat{

        public:

        static std::string FormatPath(std::string path);

    };
}


#endif