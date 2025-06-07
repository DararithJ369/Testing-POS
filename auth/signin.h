#pragma once
// #include "../include/color.h"
using namespace std;

struct signinNode{ 
    string email;
    string password;
    string name;
    string role;
    signinNode *next;
};

struct signinStack{
    int size;
    signinNode *top;
};

signinStack* createEmptySignInStack(){
    signinStack* newlist = new signinStack;
    newlist -> top = NULL;
    newlist -> size = 0;
    return newlist;
}

void pushInSignIn(signinStack* s, string email, string password, string role, string name){
    signinNode* newnode = new signinNode;
    newnode -> email = email;
    newnode -> password = password;
    newnode -> name = name;
    newnode -> role = role;
    newnode -> next = s -> top;
    s -> top = newnode;
    s -> size++;
}

string getPassInSignIn(){    
    string password;
    char ch ;
    cout << "Enter password     : " ;
    while((ch = _getch())!= '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";        
            }
        }else{
            password += ch;
            cout << "*";            
        }
    }
    cout << endl;
    return password;
}

void getAllUsersFromCSV(signinStack* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) { // Correct way to read each line
            stringstream ss(line);
            string name, ageStr, genderStr, phone, roleStr, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, roleStr, ',');
            getline(ss, email, ',');
            getline(ss, password);
            pushInSignIn(s, email, password, roleStr, name);
        }
        file.close();
    }
}

bool verifyEmailInSignIn(signinStack* s, string email){
    signinNode *temporary = s -> top;
    while (temporary != NULL){
        if (temporary -> email == email) return true;
        temporary = temporary -> next;
    } 
    return false;
}

bool verifyEmailAndPassInSignIn(signinStack *s, string email, string password){
    signinNode *temporary = s -> top;
    while (temporary != NULL){
        if (temporary -> email == email && temporary -> password == password) return true;
        temporary = temporary -> next;
    } 
    return false;
}

int verifyRoleInSignIn(signinStack *s, string email, string password){
    signinNode *temporary = s -> top;
    string role;

    ofstream user_email;
    user_email.open("../Database/temporary_user.txt", ios::out);
    user_email << email;
    user_email.close();

    while (temporary != NULL){
        if (temporary -> email == email && temporary -> password == password) {
            role = temporary -> role;
            break;
        }
        temporary = temporary -> next;
    }

    if (role == "customer") return 1;
    else if (role == "manager") return 2;
    else if (role == "admin") return 3;
    else return 0;
}

int verifyUserSignIn(){
    system("cls");
    signinStack *s = createEmptySignInStack();
    getAllUsersFromCSV(s, "../Database/users.csv");
    signinNode input;
    int count = 0;
    cout << BOLD << YELLOW << "Sign in your account" << RESET << endl;
    do{
        while (true){
            cout << "Enter email        : "; cin >> input.email;
            if (verifyEmailInSignIn(s, input.email)) break;
            else {
                system("cls");
                cout << RED << "Invalid email" << RESET << endl;
            }
        }
        system("cls");
        cout << GREEN << "Email accepted!" << RESET << endl;
        cout << "Enter email        : " << input.email << endl;
        input.password = getPassInSignIn();
        if (verifyEmailAndPassInSignIn(s, input.email, input.password)){
            cout << GREEN << "You are sign in successfully!" << RESET << endl;
            system("pause");
            return verifyRoleInSignIn(s, input.email, input.password);
        }
        else {
            system("cls");
            cout << RED << "Password incorrect! Please try again." << RESET << endl;
            continue;
        }
    } while (true);

    
}