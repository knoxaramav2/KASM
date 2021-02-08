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
    size_t len = line.size();
    string tmp;
    bool dQuote = false;
    for (size_t i = 0; i <= len; ++i){
        char c = line[i];

        //leave open for more split options
        switch(c){
            case '"':
            dQuote = !dQuote;
            if (!dQuote){
                tmp = extractString(line, idx, ++i);
                ret.push_back(tmp);
                tmp.clear();
            }
            break;
            case ' ':
            case '\t':
            case '\r':
            case '\n':
            case 0:
                if (dQuote){continue;}
                if (idx == i){
                    ++idx;
                    continue;
                } else {
                    tmp = extractString(line, idx, i);
                    ret.push_back(tmp);
                    tmp.clear();
                }
            break;
            case '\\':
                if (line[i+1] == 'n'){
                    line[i]='\r';
                    line[i+1]='\n';
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
        if (c>='A' && c<= 'Z') {
            c += 0x20;
        }

        ret += c;
    }

    return ret;
}

string Utils::ToLower(string&raw){
    return Utils::ToLower(raw.c_str());
}