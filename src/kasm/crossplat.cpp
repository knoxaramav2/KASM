#include "crossplat.hpp"
#include "limits.h"
#include <ncurses.h>

#ifdef __LINUX
    #include <unistd.h>
#endif
#ifdef __WINDOWS
    #include <libloaderapi.h>
#endif

using namespace std;
using namespace KASM;

string KCompat::String::FormatPath(string path){

    string ret;

    #ifdef __LINUX
        char pathBuff[PATH_MAX];
        auto len = readlink("/proc/self/exe", pathBuff, sizeof(pathBuff)-1);
        if (len != -1){
            ret = string(pathBuff);
        }
    #endif
    #ifdef __WINDOWS
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

bool KASM::KCompat::Graphics::SetCursorXY(int x, int y){

    //TODO Mark for linux
    

    return 0;
}

bool KASM::KCompat::Graphics::SetColor(int foreGround, int backGround){

    return 0;
}

bool KASM::KCompat::Graphics::PlotXY(int x, int y, char c){

    mvwaddch(nullptr, y, x, c);
    refresh();

    return 0;
}

bool KASM::KCompat::Graphics::ReizeTerminal(int x, int y){

    return 0;
}