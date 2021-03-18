#include "crossplat.hpp"
#include "limits.h"
#include "err.hpp"

#include <ncurses.h>
#include <stdlib.h>

#ifdef __LINUX
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif
#ifdef __WINDOWS
    #include <libloaderapi.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
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

//returns false for illegal arguments
bool KCompat::Graphics::SetCursorXY(int x, int y){

    //TODO Mark for linux
    
    int w = GetTerminalAttribute(WIDTH);
    int h = GetTerminalAttribute(HEIGHT);

    if ((x < 0 || y < 0) || (x >= w || h >= y)){
        return false;
    }

    move(y, x);
    refresh();

    return true;
}

int KCompat::Graphics::GetCursorXY(TerminalXY dim){

    int ret = 0;

    int x = 0;
    int y = 0;

    getyx(stdscr, y, x);

    if (dim == XPOS) { ret = x;}
    else if (dim == YPOS) { ret = y;}
    else return -ERR_ILLEGAL_ARG;

    return ret;
}

bool KCompat::Graphics::SetColor(int foreGround, int backGround){

    return true;
}

bool KCompat::Graphics::PlotXY(int x, int y, string str){

    //mvaddch(y, x, c);
    mvprintw(y, x, str.c_str());
    refresh();
    return true;
}

bool KCompat::Graphics::ReizeTerminal(int x, int y){

    return true;
}

int KCompat::Graphics::GetTerminalAttribute(TerminalWH ta){

    int ret = 0;
    int err = 0;
    struct winsize wsize;

    err = ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    
    if (err != 0){
        return -err;
    }
    
    switch(ta){
        case WIDTH: 
            ret = wsize.ws_col;
        break;
        case HEIGHT: 
            ret = wsize.ws_row;
        break;
        default: return ErrCode::ERR_ILLEGAL_ARG; break;
    }

    return ret;
}