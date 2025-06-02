#include <iostream> 
#include <string>
#include <windows.h>
#include "color.h"
#include "registration.h"
#include "signin.h"
using namespace std;

enum LOGIN{
    SIGNUP = 1,
    SIGNIN,
    EXIT
};

int Introduction(){
    int option;
    cout << " ____    ___   ____    ____            _                 " << endl;
    cout << "|  _ \\ / _ \\/ ___|  / ___| _   _ ___| |_ ___ _ __ ___  " << endl;
    cout << "| |_) | | | \\___ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
    cout << "|  __/| |_| |___) |  ___) | |_| \\__ \\ ||  __/ | | | | |" << endl;
    cout << "|_|    \\___/|____/  |____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
    cout << "                           |___/                       " << endl;
    cout << endl;
    cout << "Create or signin an account to continue our system " << endl;  
    cout << " 1. Create account                                 " << endl; 
    cout << " 2. Sign in to your account                        " << endl;
    cout << " 3. Exit the program                               " << endl;
    cout << "===================================================" << endl;
    cout << " Select an option to continue: " << YELLOW; cin >> option; cout << RESET;
    return option;
}


void ExIT(int time){
    for (int i = time; i > 0; i--){
        system("cls");
        cout << "The system will shut down in " << MAGENTA << i << RESET << ((i <= 1) ? " second" : " seconds");
        Sleep(1000);
    }
    system("cls");
    cout << "Goodbye! Have a nice day!\n" << endl;
    cout << system("pause"); cout << RESET;
    system("cls");
    exit(0);
}

int login(){
    system("cls");
    while (true){
        switch (Introduction()){
            case SIGNUP:return verifyEmailAndPassFromUser();break;
            case SIGNIN: return verifyUserSignIn(); break;
            case EXIT:ExIT(3);break;
            default:break;
        }
    }
}

