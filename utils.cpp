#include "utils.hpp"

#include <iostream>
#include <string.h>

using namespace std;
using namespace KASM;

string extractString(string& raw, size_t& start, size_t end){
    size_t s = start;
    string ret = raw.substr(start++, end-s);
    start = end + 1;
    return ret;
}

//split by whitespace
vector<string> Utils::SplitString(string line){


    vector<string> ret;
    size_t idx = 0;
    string tmp;
    for (size_t i = 0; i <= line.size(); ++i){
        char c = line[i];

        //leave open for more split options
        switch(c){
            case ' ':
            case '\t':
            case '\r':
            case '\n':
            case 0:
                if (idx == i){
                    ++idx;
                    continue;
                } else {
                    tmp = extractString(line, idx, i);
                    ret.push_back(tmp);
                    tmp.clear();
                }
            break;
            default:
            break;
        }
    }

#ifdef __DEBUG
    for(size_t i=0; i<ret.size(); ++i){
        //cout << "[" << ret[i] << "] ";
    }
#endif

    cout << endl;

    return ret;
}

string Utils::ToUpper(const char raw[]){

    string ret;

    for(size_t i=0; i < strlen(raw); ++i){
        char c = raw[i];
        if (c>='a' && c<= 'z') {
            c -= 0x20;
        }

        ret += c;
    }

    return ret;
}

string Utils::ToUpper(string&raw){
    return Utils::ToUpper(raw.c_str());
}

string Utils::ToLower(const char raw[]){

    string ret;

    for(size_t i=0; i < strlen(raw); ++i){
        char c = raw[i];
        if (c>='a' && c<= 'z') {
            c += 0x20;
        }

        ret += c;
    }

    return ret;
}

string Utils::ToLower(string&raw){
    return Utils::ToLower(raw.c_str());
}