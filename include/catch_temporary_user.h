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

void saveEmailToTemporaryFile(string email) {
    ofstream file("../Database/temporary_user.txt", ios::out);
    if (file.is_open()) {
        file << email;
        file.close();
    }
}