#include<iostream>
#include<fstream>
#include<conio.h>
#include<cctype>
#include<string>
#include<sstream>
#include"color.h"
using namespace std;

struct Element{
    string name, email, password, role;
    Element* next;
};

struct signUpStack{
    int size;
    Element* top;
};

signUpStack *createSignUpStack(){
    signUpStack *stack = new signUpStack;
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void pushInSignUpStack(signUpStack *stack, string email){
    Element *newElement = new Element;
    newElement->email = email;
    newElement->next = stack->top;
    stack->top = newElement;
    stack->size++;
}

void displaySignUpStack(signUpStack *stack){
    Element *current = stack->top;
    cout << "Registered Emails:" << endl;
    while (current != NULL) {
        cout << current->email << endl;
        current = current->next;
    }
}

void readAllUsersFromCSV(signUpStack *stack, string filePath){
    ifstream file;
    file.open(filePath, ios::in);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            stringstream ss(line);
            string name, email, password, roleStr;
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, password, ',');
            getline(ss, roleStr, ',');
            pushInSignUpStack(stack, email);
        }
        file.close();
    }
    else{
        cout << RED << "Error opening file: " << filePath << RESET << endl;
    }
}

void writeUserToCSV(string name, string email, string password, string role, string filePath){
    ofstream file;
    file.open(filePath, ios::app);
    if(file.is_open()){
        file << name << "," << email << "," << password << "," << role << endl;
        file.close();
        cout << GREEN << "Registered successfully!" << RESET << endl;
    }
    else{
        cout << RED << "Error opening file: " << filePath << RESET << endl;
    }
}

string getPassword(){
    string password;
    char ch ;
    cout << "Enter password: " ;
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

string verifyPassword(){
    string password;
    char ch;
    cout << "Re-enter password: ";
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

// Checks if the provided email has a valid format: contains '@' and a '.' after '@'
bool isValidEmail(string email) {
    // Use int for positions instead of size_t
    int atPos = email.find('@');
    int dotPos = email.find('.', atPos);
    // Check if '@' and '.' exist in the email
    if (atPos == -1 || dotPos == -1) return false;
    // '@' should not be the first character
    if (atPos == 0) return false;
    // '.' must come after '@' and not immediately after
    if (dotPos <= atPos + 1) return false;
    // '.' should not be the last character
    if (dotPos == email.length() - 1) return false;
    return true;
}

bool isEmailRegistered(signUpStack *stack, string email) {
    if (!isValidEmail(email)) {
        return false; // Invalid email format
    }
    Element *current = stack->top;
    while (current != NULL) {
        if (current->email == email) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int registerUser(){
    system("cls");
    signUpStack *s = createSignUpStack();
    string filename = "Database/users.csv";
    readAllUsersFromCSV(s, filename);
    Element input;
    cout << BOLD << "Register a new user" << RESET << endl;
    cin.ignore(); // Clear the input buffer before taking string input

    // Prompt for name once
    cout << "Enter your name: ";
    getline(cin, input.name);

    // Loop for email until valid and not registered
    while (true) {
        cout << "Enter your email: ";
        getline(cin, input.email);
        if (isEmailRegistered(s, input.email)) {
            cout << RED << "Email already registered. Please try another email." << RESET << endl;
            continue;
        }
        break;
    }

    // Password input and confirmation
    while (true) {
        input.password = getPassword();
        string confirmPassword = verifyPassword();
        if (input.password != confirmPassword) {
            cout << RED << "Passwords do not match. Please try again." << RESET << endl;
            continue;
        }
        break;
    }

    // Set default role
    input.role = "customer";
    // Write to CSV
    writeUserToCSV(input.name, input.email, input.password, input.role, filename);

    return 0;
}