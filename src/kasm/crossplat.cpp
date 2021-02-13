#include "crossplat.hpp"
#include "limits.h"

#ifdef __LINUX
    #include <unistd.h>
#endif
#ifdef __WINDOWS
    #include <libloaderapi.h>
#endif

using namespace std;
using namespace KASM;

string KCompat::FormatPath(string path){

    string ret;

    #ifdef __LINUX
        char pathBuff[PATH_MAX];
        auto len = readlink("/proc/self/exe", pathBuff, sizeof(pathBuff)-1);
        if (len != -1){
            ret = string(pathBuff);
        }
    #else
        TCHAR pathBuff[MAX_PATH];
        GetModuleFileName(nullptr, pathBuff, MAX_PATH);
        ret = pathBuff;

    #endif

    size_t dirszf = ret.find_last_of('/');
    size_t dirszb = ret.find_last_of('\\');    
    size_t cutoff = dirszf == string::npos ? 0 : dirszf;

    if (dirszb != string::npos && dirszb > cutoff) { cutoff = dirszb; }

    ret = ret.substr(0, cutoff) + "/";

    return ret+path;
}