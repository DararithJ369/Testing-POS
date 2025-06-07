#pragma once
using namespace std;

string catchEmailFromTemporaryEmail(){
    ifstream file;
    string email;
    file.open("../Database/temporary_user.txt", ios::in);
    getline(file >> ws, email);
    file.close();
    return email;
}
