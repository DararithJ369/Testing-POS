#pragma once
#include <string>
#include <fstream>
#include <ctime>
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

inline void logUserAction(const string& email, const string& action) {
    ofstream log("Database/userlog.txt", ios::app);
    if (!log.is_open()) return;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char datetime[32];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", ltm);
    log << "[" << datetime << "] " << email << ": " << action << endl;
    log.close();
}