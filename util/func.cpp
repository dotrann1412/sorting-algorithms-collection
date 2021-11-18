#include "func.h"

void _replace(std::string& s, char src, char dest) {
    //std::string t = "";
    //for(char x: s) if(x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z' || x == '_') t += x;
    for(char& c: s) 
        if(c == src) c = dest;
    //s = t;
}