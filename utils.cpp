#include "utils.hpp"

#include <iostream>

using namespace std;
using namespace KASM;

string extractString(string& raw, size_t& start, size_t end){
    size_t s = start;
    string ret = raw.substr(start++, end-s);
    start = end + 1;
    return ret;
}

//split by whitespace, preserve quotes
vector<string> Utils::SplitString(string line){

    vector<string> ret;

    bool dQuote = false;
    bool sQuote = false;
    size_t idx = 0;
    string tmp;
    for (size_t i = 0; i <= line.size(); ++i){
        char c = line[i];

        switch(c){
            case '\'':
                if (sQuote){

                } else {

                }
            break;
            case '"':
                if (dQuote){

                } else {

                }
            break;
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

    for(size_t i=0; i<ret.size(); ++i){
        cout << "[" << ret[i] << "] ";
    }

    cout << endl;

    return ret;
}