#include<iostream>
#include<string>
#include"registration.h"
#include"signin.h"
#include"color.h"
using namespace std;

enum LOGIN{
    SIGNUP = 1,
    SIGNIN,
    EXIT
};

int displayLoginMenu(){
    int choice;
    system("cls");
    cout << BOLD << "Welcome to the POS System" << RESET << endl;
    cout << "Login your account before start the program" << endl;
    cout << "1. Create account" << endl;
    cout << "2. Sign in" << endl;
    cout << "3. End program" << endl;
    cout << "Please select an option: "; cin >> choice;
    return choice;
}

int authenticateUser() {
    system("cls");
    string filename = "Database/users.csv";
    while(true){
        switch(displayLoginMenu()){
            case SIGNUP: {
                system("cls");
                signUpStack *s = createSignUpStack();
                readAllUsersFromCSV(s, filename);
                registerUser();
                break;
            }
            case SIGNIN: {
                return verifyUserSignIn();
            }
            case EXIT: {
                cout << "Exiting the program." << endl;
                exit(0);
            }
        }
    }
}