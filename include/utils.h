#pragma once
#include <string>
using namespace std;

inline bool isAllAlphabets(string str) {
    for (char ch : str) { if (!(isalpha(ch) || isspace(ch))) return false; }
    return true;
}

inline bool isAllDigits(string str) {
    for (char ch : str) { if (!isdigit(ch)) return false; }
    return true;
}