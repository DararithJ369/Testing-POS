#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include"color.h"
using namespace std;

struct signInElement{
    string email, password, role, name;
    signInElement *next;
};

struct signInStack{
    int size;
    signInElement *top;
};

signInStack *createSignInStack(){
    signInStack *stack = new signInStack;
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void pushInSignIn(signInStack *s, string email, string password, string role, string name){
    signInElement *newElement = new signInElement;
    newElement->email = email;
    newElement->password = password;
    newElement->role = role;
    newElement->name = name;
    newElement->next = s->top;
    s->top = newElement;
    s->size++;
}

string getPasswordInSignIn(){
    string password;
    char ch;
    cout << "Enter Password: ";
    while((ch = _getch()) != '\r') { // '\r' is the Enter key
        if(ch == '\b') { // Backspace key
            if(!password.empty()) {
                password.pop_back(); // remove last character from string
                cout << "\b \b"; // Move cursor back, print space, move back again
            }
        } 
        else {
            password += ch; // add character to password
            cout << '*'; // display asterisk for each character
        }
    }
    cout << endl; // move to next line after password input
    return password;
}

void getAllUsersFromCSVInSignIn(signInStack *s, const string &filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, email, password, role;
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, password, ',');
            getline(ss, role);
            if (!email.empty() && !password.empty() && !role.empty()) {
                pushInSignIn(s, email, password, role, name);
            }
        }
        file.close();
    } else {
        cout << RED << "Error opening file: " << filename << RESET << endl;
    }
}

bool isEmailExistsInSignIn(signInStack *s, const string &email) {
    signInElement *current = s->top;
    while(current != NULL) {
        if(current->email == email) {
            return true; // Email exists
        }
        current = current->next;
    }
    return false; // Email does not exist
}

bool verifyPasswordAndEmailInSignIn(signInStack *s, const string &email, const string &password) {
    signInElement *current = s->top;
    while(current != NULL) {
        if(current->email == email && current->password == password) {
            return true; // Email and password match
        }
        current = current->next;
    }
    return false; // Email or password does not match
}

int verifyRoleInSignIn(signInStack *s, string email, string password) {
    signInElement *current = s->top;
    string role;
    while(current != NULL) {
        if(current->email == email) {
            role = current->role;
            break; // Found the email, exit loop
        }
        current = current->next;
    }
    
    // Example mapping
    if(role == "user") return 1;      // CUSTOMER
    if(role == "admin") return 2;     // ADMIN
    if(role == "manager") return 3;   // MANAGER
    if(role == "cashier") return 4;   // CASHIER
    return 0; // For invalid role
}

int verifyUserSignIn(){
    system("cls");
    signInStack *s = createSignInStack();
    string filename = "Database/users.csv";
    getAllUsersFromCSVInSignIn(s, filename);
    signInElement input;
    do{
        cout << "Sign In Statement\n";
        while(true){
            cout << "Enter your email: ";
            cin >> input.email;
            if(isEmailExistsInSignIn(s, input.email)){
                break; // Email exists, exit loop
            }
            else{
                system("cls");
                cout << RED << "Email does not exist! Please try again." << RESET << endl;
            }
        }
        system("cls");
        cout << GREEN << "Email is accepted." << RESET << endl;
        cout << "Enter your email: " << YELLOW << input.email << RESET << endl;
        input.password = getPasswordInSignIn();
        if(verifyPasswordAndEmailInSignIn(s, input.email, input.password)){
            system("cls");
            cout << GREEN << "Login successful!" << RESET << endl;
            return verifyRoleInSignIn(s, input.email, input.password); // Return role based on email
        } 
        else {
            system("cls");
            cout << RED << "Invalid email or password! Please try again." << RESET << endl;
            continue; // Retry login
        }
    }
    while(true);
}