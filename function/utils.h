#pragma once
#include <string>
using namespace std;

bool isAllAlphabets(string str) {
    for (char ch : str) {if (!(isalpha(ch) || isspace(ch))) return false;}
    return true;    
}

bool isAllDigits(string str) {
    for (char ch : str) {if (!isdigit(ch)) return false;}
    return true;
}

string Capitalization(string index){
    string cap;
    bool isFirst = true;
    for(char c : index){
        if(isFirst){cap += toupper(c); isFirst = false;}
        else if(c == ' '){cap += c; isFirst = true;}
        else cap += c;
    }
    return cap;
}