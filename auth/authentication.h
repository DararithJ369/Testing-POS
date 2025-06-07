#include <iostream> 
#include "registration.h"
#include "signin.h"
using namespace std;

enum LOGIN{
    SIGNUP = 1,
    SIGNIN,
    EXIT
};

int count = 0;
int Introduction(){
    int option;
    cout << " ____   ___  ____    ____            _                 " << endl;
    cout << "|  _ \\ / _ \\/ ___|  / ___| _   _ ___| |_ ___ _ __ ___  " << endl;
    cout << "| |_) | | | \\___ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
    cout << "|  __/| |_| |___) |  ___) | |_| \\__ \\ ||  __/ | | | | |" << endl;
    cout << "|_|    \\___/|____/  |____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
    cout << "                           |___/                       " << endl;
    cout << endl;
    if(count == 0){
        cout << GRAY; system ("pause"); cout << RESET << endl;
    }
    cout << "Create or signin an account to continue our system " << endl;  
    cout << "   1. Create account                                 " << endl; 
    cout << "   2. Sign in to your account                        " << endl;
    cout << "   3. Exit the program                               " << endl;
    cout << BOLD << string(50, '-') << RESET << endl;
    cout << "Select an option to continue: "; cin >> option;
    if(cin.fail()){cin.clear(); cin.ignore(10000, '\n'); return -1;}
    return option;
}

void ExIT(int time){
    for (int i = time; i > 0; i--){
        system("cls");
        cout << "The system will shut down in " << RED << i << RESET << ((i <= 1) ? " second" : " seconds");
        Sleep(1000);
    }
    system("cls");
    cout << "Goodbye! Have a nice day!" << endl;
    cout << system("pause"); cout << RESET;
    system("cls");
    exit(0);
}

int login(){
    string currentEmail;
    while (true){
        system("cls");
        switch (Introduction()){
            case SIGNUP:{
                int result = verifyEmailAndPassFromUser();
                currentEmail = catchEmailFromTemporaryEmail();
                logUserAction(currentEmail, "Signed up");
                return result;
            }
            case SIGNIN: {
                int result = verifyUserSignIn();
                currentEmail = catchEmailFromTemporaryEmail(); 
                logUserAction(currentEmail, "Logged in");
                return result;
            }
            case EXIT: ExIT(3); break;
            default:
                cout << RED << "Invalid input! Please try again." << RESET << endl;
                system("pause");
                break;
        }
        count++;
    }
}