#pragma once
#include <iostream>
#include "color.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include "utils.h"
using namespace std;

struct funcUserNode{
    // user management
    string name, role, email, password, phone;
    char gender;
    int age;
    funcUserNode* next;
    funcUserNode* prev;
};

struct funcListUser{
    int size;
    funcUserNode* head;
    funcUserNode* tail;
};

funcListUser* createfuncListUser() {
    funcListUser* list = new funcListUser;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

bool isValidEmail(string email) {
    return email.size() >= 10 && email.substr(email.size() - 10) == "@gmail.com";
}

bool isEmailExists(funcListUser* list, string email) {
    funcUserNode* current = list->head;
    while (current) {
        if (current->email == email) return true;
        current = current->next;
    }
    return false;
}

bool isValidPhone(string phone) {
    return (phone.size() == 9 || phone.size() == 10) && phone[0] == '0' && isAllDigits(phone);
}

string toLower(string str) {
    string lowerStr;
    for(char ch : str){
        ch = tolower(ch);
        lowerStr += ch;
    }
    return lowerStr;
}

void funcAddUserToBegin(funcListUser* list, string name, int age, char gender, string phone, string role, string email, string password) {
    funcUserNode* newNode = new funcUserNode;
    newNode->name = name;
    newNode->age = age;
    newNode->gender = gender;
    newNode->phone = phone;
    newNode->role = role;
    newNode->email = email;
    newNode->password = password;
    newNode->next = list->head;
    newNode->prev = nullptr;
    if (list->head != nullptr) {
        list->head->prev = newNode;
    } else {
        list->tail = newNode; // If list was empty, tail is now newNode
    }
    list->head = newNode;
    list->size++;
}

void funcAddUserToEnd(funcListUser* list, string name, int age, char gender, string phone, string role, string email, string password) {
    funcUserNode* newNode = new funcUserNode;
    newNode->name = name;
    newNode->age = age;
    newNode->gender = gender;
    newNode->phone = phone;
    newNode->role = role;
    newNode->email = email;
    newNode->password = password;
    newNode->next = nullptr;
    newNode->prev = list->tail;
    if (list->tail != nullptr) {
        list->tail->next = newNode;
    } else {
        list->head = newNode; // If list was empty, head is now newNode
    }
    list->tail = newNode;
    list->size++;
}

void funcAddUserAt(funcListUser* list, int pos, string name, int age, char gender, string phone, string role, string email, string password) {
    funcUserNode* newNode = new funcUserNode;
    newNode->name = name;
    newNode->gender = gender;
    newNode->age = age;
    newNode->phone = phone;
    newNode->role = role;
    newNode->email = email;
    newNode->password = password;
    if(pos == 1 || list->size == 0) funcAddUserToBegin(list, name, age, gender, phone, role, email, password);
    else if(pos > list->size) funcAddUserToEnd(list, name, age, gender, phone, role, email, password);
    else {
        funcUserNode* current = list->head;
        for(int i = 1; i < pos - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if(current->next) current->next->prev = newNode;
        current->next = newNode;
        if(newNode->next == nullptr) list->tail = newNode; // Update tail if added at the end
        list->size++;
    }
} 

void funcDeleteUserBegin(funcListUser* list) {
    if (list->size == 0) return;
    funcUserNode* temp = list->head;
    if (temp->next) temp->next->prev = nullptr;
    else list->tail = nullptr; // If it was the only node
    list->head = temp->next;
    delete temp;
    list->size--;
}

void funcDeleteUserEnd(funcListUser* list) {
    if (list->size == 0) return;
    funcUserNode* temp = list->tail;
    if (temp->prev) temp->prev->next = nullptr;
    else list->head = nullptr; // If it was the only node
    list->tail = temp->prev;
    delete temp;
    list->size--;
}

void funcDeleteUserAt(funcListUser* list, int pos) {
    if (list->size == 0 || pos < 1 || pos > list->size) return;
    if (pos == 1) {
        funcDeleteUserBegin(list);
        return;
    }
    if (pos == list->size) {
        funcDeleteUserEnd(list);
        return;
    }
    funcUserNode* current = list->head;
    for (int i = 1; i < pos; ++i) current = current->next;

    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    delete current;
    list->size--;
}

void funcLoadUsers(funcListUser* list, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) { cout << "Cannot open file!" << endl; return; }
    else {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, genderStr, ageStr, phone, role, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, role, ',');
            getline(ss, email, ',');
            getline(ss, password);
            char gender = genderStr.empty() ? ' ' : genderStr[0];
            int age = stoi(ageStr);
            funcAddUserToEnd(list, name, age, gender, phone, role, email, password);
        }
    }
    file.close();
}

void funcDisplayUsers(funcListUser* list, bool check) {
    system("cls");
    int n0 = 1;
    funcUserNode* current = list->head;
    cout << YELLOW << "All users information in the system\n" << RESET;
    cout << string(104, '-') << endl;
    cout << left 
         << setw(5)  << "No" 
         << setw(20) << "Name" 
         << setw(6)  << "Age" 
         << setw(8)  << "Gender" 
         << setw(15) << "Phone" 
         << setw(12) << "Role"
         << setw(30) << "Email"
         << setw(20) << "Password"
         << endl;
    cout << string(104, '-') << endl;
    while(current != NULL){
        cout << left
             << setw(5)  << n0
             << setw(20) << current->name
             << setw(6)  << current->age
             << setw(8)  << current->gender
             << setw(15) << current->phone
             << setw(12) << current->role
             << setw(30) << current->email
             << setw(20) << current->password
             << endl;
        current = current->next;
        n0++; 
    }
    
    cout << string(104, '-') << endl;
    cout << YELLOW << "Total users: " << list->size << RESET << endl << endl;
    if(check){ system("pause"); system("cls");}
}

void funcSaveUsers(funcListUser* list, string filename) {
    ofstream file(filename);
    if (!file.is_open()) { cout << "Cannot write to file!" << endl; return; }
    funcUserNode* current = list->head;
    while (current != NULL) {
        file << current->name << "," << current->age << "," << current->gender << "," << current->phone << "," << current->role << "," << current->email << "," << current->password << "\n";
        current = current->next;
    }
    file.close();
}

void funcSearchUserByEmail(funcListUser*list){
    system("cls");
    string email;
    bool found = false;
    funcUserNode* current = list->head;
    cout << VIOLET << "Search user information by email\n" << RESET;
    cout << "---------------------------------------------\n";
    // all emails in system
    cout << YELLOW << "All emails in the system:\n" << RESET;
    int n0 = 1;
    while(current != NULL){
        cout << n0 << ". ";
        cout << current->email << endl;
        current = current->next;
        n0++;
    }
    cout << "---------------------------------------------\n\n";
    cout << "Enter email to search: ";
    getline(cin >> ws, email);
    system("cls");
    current = list->head;
    while(current != NULL){
        if(current->email == email){
            cout << GREEN << current->name << " | Current User Information\n" << RESET;
            cout << string(50, '-') << endl;
            cout << "Current Information:\n";
            cout << "Name: " << current->name << endl;
            cout << "Gender: " << current->gender << endl;
            cout << "Age: " << current->age << endl;
            cout << "Phone: " << current->phone << endl;
            cout << "Role: " << current->role << endl;
            cout << "Email: " << current->email << endl;
            cout << "Password: " << current->password << endl;
            cout << string(50, '-') << endl << endl;
            found = true;
            break;
        }
        current = current->next;
    }
    if(!found) {
        cout << RED << "No user found with email: " << email << RESET << endl;
    }
    system("pause");
}

void funcDeleteUserByEmail(funcListUser* list) {
    funcUserNode* current = list->head;
    string email;
    system("cls");
    funcDisplayUsers(list, 0);
    cout << VIOLET << "Delete user by email\n" << RESET;
    cout << "---------------------------------------------\n";
    if (list->size == 0) {
        cout << RED << "No users available to delete." << RESET << endl;
        system("pause");
        return;
    }
    cout << "Enter email to delete: ";
    getline(cin >> ws, email);

    if (!isValidEmail(email)) {
        cout << RED << "Invalid email format! Please enter a valid email (must end with @gmail.com)." << RESET << endl << endl;
        system("pause");
        return;
    }
    system("cls");
    while (current) {
        if (current->email == email) {
            if (current->prev) current->prev->next = current->next;
            else list->head = current->next; // If deleting head
            if (current->next) current->next->prev = current->prev;
            else list->tail = current->prev; // If deleting tail
            delete current;
            list->size--;
            cout << GREEN << "User with email " << RED << email << GREEN << " has been deleted successfully." << RESET << endl << endl;
            break;
        }
        current = current->next;
    }
    funcSaveUsers(list, "Database/users.csv");
    system("pause");
}

string funcNameMod(string newName){
    while(true){
        cout << "Current name: " << newName << endl;
        cout << "Enter new name: ";
        getline(cin >> ws, newName);
        system("cls");
        if(isAllAlphabets(newName)) {
            cout << GREEN << "New name has been changed successfully\n" << RESET << endl;
            return newName;
        }
        else {
            cout << RED << "Invalid name! Please enter a valid name (only alphabets and spaces allowed).\n" << RESET << endl;
            continue;
        }
    }
}

char funcGenderMod(char newGender){
    while(true){
        cout << "Current gender: " << newGender << endl;
        cout << "Enter new gender (M/F): ";
        cin >> newGender;
        newGender = toupper(newGender);
        system("cls");
        if(newGender == 'M' || newGender == 'F') {
            cout << GREEN << "New gender has been changed successfully\n" << RESET << endl;
            return newGender;
        }
        else {
            cout << RED << "Invalid gender! Please enter 'M' or 'F'.\n" << RESET << endl;
            continue;
        }
    }
}

int funcAgeMod(int newAge){
    while(true){
        cout << "Current age: " << newAge << endl;
        cout << "Enter new age: ";
        cin >> newAge;
        system("cls");
        if(newAge > 0 && newAge < 150) {
            cout << GREEN << "New age has been changed successfully\n" << RESET << endl;
            return newAge;
        }
        else {
            cout << RED << "Invalid age! Please enter a valid age (between 1 and 149).\n" << RESET << endl;
            continue;
        }
    }
}

string funcPhoneMod(string newPhone){
    while(true){
        cout << "Current phone number: " << newPhone << endl;
        cout << "Enter new phone number: ";
        getline(cin >> ws, newPhone);
        system("cls");
        if(isValidPhone(newPhone)) {
            cout << GREEN << "New phone has been changed successfully\n" << RESET << endl;
            return newPhone;
        }
        else {
            cout << RED << "Invalid phone! Please enter a valid phone number (must start with 0 and be 9 or 10 digits long).\n" << RESET << endl;
            continue;
        }
    }
}

string funcRoleMod(string newRole){
    while(true){
        cout << "Current role: " << newRole << endl;
        cout << "Enter new role (admin, manager, customer): ";
        cin >> newRole;
        newRole = toLower(newRole);
        system("cls");
        if(newRole == "admin" || newRole == "manager" || newRole == "customer") {
            cout << GREEN << "New role has been changed successfully\n" << RESET << endl;
            return newRole;
        }
        else {
            cout << RED << "Invalid role! Please enter a valid role (admin, manager, customer).\n" << RESET << endl;
            continue;
        }
    }
}

string funcEmailMod(string newEmail){
    while(true){
        cout << "Current email: " << newEmail << endl;
        cout << "Enter new email: ";
        getline(cin >> ws, newEmail);
        system("cls");
        if(isValidEmail(newEmail)) {
            cout << GREEN << "New email has been changed successfully\n" << RESET << endl;
            return newEmail;
        }
        else {
            cout << RED << "Invalid email! Please enter a valid email (must end with @gmail.com).\n" << RESET << endl;
            continue;
        }
    }
}

string funcPasswordMod(string newPassword){
    while(true){
        cout << "Current password: " << newPassword << endl;
        cout << "Enter new password: ";
        getline(cin >> ws, newPassword);
        system("cls");
        if(newPassword.length() >= 6) {
            cout << GREEN << "New password has been changed successfully\n" << RESET << endl;
            return newPassword;
        }
        else {
            cout << RED << "Invalid password! Please enter a valid password (at least 6 characters long).\n" << RESET << endl;
            continue;
        }
    }
}

void funcUpdateUserToList(funcListUser* list, int pos, string name, char gender, int age, string phone, string role, string email, string password) {
    funcDeleteUserAt(list, pos);
    funcAddUserAt(list, pos, name, gender, age, phone, role, email, password);
}

void funcUpdateUserToCSV(funcListUser* list){
    funcUserNode* current = nullptr;
    int option = 0;
    int select;
    funcDisplayUsers(list, 0);
    
    cout << "Select the user you want to update (1-" << list->size << "): ";
    cin >> select;
    cin.ignore();

    if(select <= 0 || select > list->size) {
        cout << RED << "Invalid selection! Please try again.\n" << RESET << endl;
        return funcUpdateUserToCSV(list);  // exit early on invalid input
    }

    current = list->head;
    for(int i = 1; i < select; ++i) {
        current = current->next;
    }

    system("cls");
    cout << GREEN << current->name << " | Update User Information\n" << RESET;
    cout << string(50, '-') << endl;
    cout << "Current Information:\n";
    cout << "Name       : " << current->name << endl;
    cout << "Gender     : " << current->gender << endl;
    cout << "Age        : " << current->age << endl;
    cout << "Phone      : " << current->phone << endl;
    cout << "Role       : " << current->role << endl;
    cout << "Email      : " << current->email << endl;
    cout << "Password   : " << current->password << endl;
    cout << string(50, '-') << endl << endl;

    do {
        cout << YELLOW << "Update User Information Menu:\n" << RESET;
        cout << "1. Update Name\n";
        cout << "2. Update Gender\n";
        cout << "3. Update Age\n";
        cout << "4. Update Phone\n";
        cout << "5. Update Role\n";
        cout << "6. Update Email\n";
        cout << "7. Update Password\n";
        cout << "8. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> option;

        switch(option) {
            case 1: system("cls"); current->name = funcNameMod(current->name); break;
            case 2: system("cls"); current->gender = funcGenderMod(current->gender); break;
            case 3: system("cls"); current->age = funcAgeMod(current->age); break;
            case 4: system("cls"); current->phone = funcPhoneMod(current->phone); break;
            case 5: system("cls"); current->role = funcRoleMod(current->role); break;
            case 6: system("cls"); current->email = funcEmailMod(current->email); break;
            case 7: system("cls"); current->password = funcPasswordMod(current->password); break;
            case 8: {system("cls"); cout << YELLOW << "Returning to the previous menu..." << RESET << endl; system("pause"); system("cls"); return;} // exit update menu
            default: cout << RED << "Invalid option! Please try again.\n" << RESET; break;
        }

        funcUpdateUserToList(list, select, current->name, current->age, current->gender, current->phone, current->role, current->email, current->password);

        char choice = 'P';
        while(choice != 'Y' && choice != 'N') {
            cout << "Do you want modify something else? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            switch(choice){
                case 'Y': system("cls"); cout << GREEN << "The information has been changed successfully\n" << RESET << endl; break;
                case 'N': system("cls"); funcSaveUsers(list, "Database/users.csv"); return;
                default: cout << RED << "Invalid choice! Please enter Y or N.\n" << RESET << endl;
            }
        }

    } while(option != 8);
}

void addNewUsers(funcListUser* list) {
    string name, email, password, phone, role;
    char gender;
    int age;
    bool validInput = false;
    while (!validInput) {
        bool check = true;
        system("cls");
        do{
            system("cls");
            cout << VIOLET << "Add New User" << RESET << endl << endl;
            if(!check) cout << RED << "Invalid name! Name shouldn't have symbol or number!" << RESET << endl;
            cout << "Full name: "; getline(cin >> ws, name);
            check = isAllAlphabets(name);
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid age! Please enter age (1-99)!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: "; cin >> age;
            check = (age >= 0 && age <= 100);
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid gender! Please enter (M/F)!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender (M/F): "; cin >> gender;
            gender = toupper(gender);
            check = (gender == 'M' || gender == 'F');
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid phone number!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender (M/F): " << gender << endl;
            cout << "Phone number: "; getline(cin >> ws, phone);
            check = isValidPhone(phone);
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid role! Please enter (admin, manager, cashier, customer)!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender (M/F): " << gender << endl;
            cout << "Phone number: " << phone << endl;
            cout << "Role (admin, manager, cashier, customer): "; cin >> role;
            role = toLower(role);
            check = (role == "admin" || role == "manager" || role == "cashier" || role == "customer");
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid email! Please enter a valid email (must end with @gmail.com)!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender (M/F): " << gender << endl;
            cout << "Phone number: " << phone << endl;
            cout << "Role (admin, manager, cashier, customer): " << role << endl;
            cout << "Email (must end with @gmail.com): "; getline(cin >> ws, email);
            check = isValidEmail(email) && !isEmailExists(list, email);
        } while (!check);
        do {
            system("cls");
            cout << VIOLET << "\t\tAdd New User\n";
            cout << "---------------------------------------\n" << RESET;
            if(!check) cout << RED << "Invalid password! Please enter a valid password (at least 6 characters long)!" << RESET << endl;
            cout << "Full name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender (M/F): " << gender << endl;
            cout << "Phone number: " << phone << endl;
            cout << "Role (admin, manager, cashier, customer): " << role << endl;
            cout << "Email (must end with @gmail.com): " << email << endl;
            cout << "Password (at least 6 characters long): "; getline(cin >> ws, password);
            check = (password.length() >= 6);
        } while (!check);

        funcAddUserToEnd(list, name, age, gender, phone, role, email, password);
        char choice = 'P';
        while(choice != 'Y' && choice != 'N') {
            cout << "Do you want to add another user? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            switch(choice){
                case 'Y': system("cls"); cout << GREEN << "New user has been added successfully!\n" << RESET; break;
                case 'N': system("cls"); funcSaveUsers(list, "Database/users.csv"); validInput = true; break;
                default: cout << RED << "Invalid choice! Please enter Y or N.\n" << RESET << endl;
            }
        }
        
    }
}

void funcModifyOwnInfo(funcListUser* list, string loggedEmail){
    funcUserNode* current = list->head;
    int option = 0;
    int select;
    system("cls");
    while(current != NULL){
        if(current->email == loggedEmail){
            cout << GREEN << current->name << " | Current User Information\n" << RESET;
            cout << string(50, '-') << endl;
            cout << "Current Information:\n";
            cout << "Name       : " << current->name << endl;
            cout << "Gender     : " << current->gender << endl;
            cout << "Age        : " << current->age << endl;
            cout << "Phone      : " << current->phone << endl;
            cout << "Role       : " << current->role << endl;
            cout << "Email      : " << current->email << endl;
            cout << string(50, '-') << endl << endl;
            // found = true;
            break;
        }
        current = current->next;
    }

    do {
        cout << YELLOW << "Update your information\n" << RESET;
        cout << "1. Update Name\n";
        cout << "2. Update Gender\n";
        cout << "3. Update Age\n";
        cout << "4. Update Phone\n";
        cout << "5. Update Email\n";
        cout << "6. Update Password\n";
        cout << "7. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> option;

        switch(option) {
            case 1: system("cls"); current->name = funcNameMod(current->name); break;
            case 2: system("cls"); current->gender = funcGenderMod(current->gender); break;
            case 3: system("cls"); current->age = funcAgeMod(current->age); break;
            case 4: system("cls"); current->phone = funcPhoneMod(current->phone); break;
            case 5: system("cls"); current->email = funcEmailMod(current->email); break;
            case 6: system("cls"); current->password = funcPasswordMod(current->password); break;
            case 7: system("cls"); return; // exit update menu
            default: cout << RED << "Invalid option! Please try again.\n" << RESET; break;
        }

        funcUpdateUserToList(list, select, current->name, current->age, current->gender, current->phone, current->role, current->email, current->password);

        char choice = 'P';
        while(choice != 'Y' && choice != 'N') {
            cout << "Do you want modify something else? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            switch(choice){
                case 'Y': system("cls"); cout << GREEN << "The information has been changed successfully\n" << RESET << endl; break;
                case 'N': system("cls"); funcSaveUsers(list, "Database/users.csv"); return;
                default: cout << RED << "Invalid choice! Please enter Y or N.\n" << RESET << endl;
            }
        }

    } while(option != 7);    
}

void displayOwnInfo(funcListUser* userList, string loggedEmail) {
    funcUserNode* current = userList->head;
    while (current) {
        if (current->email == loggedEmail) {
            cout << YELLOW << "Your Information:\n" << RESET;
            cout << "Name       : " << current->name << endl;
            cout << "Gender     : " << current->gender << endl;
            cout << "Age        : " << current->age << endl;
            cout << "Phone      : " << current->phone << endl;
            cout << "Role       : " << current->role << endl;
            cout << "Email      : " << current->email << endl;
            return;
        }
        current = current->next;
    }
    cout << RED << "No user found with email: " << loggedEmail << RESET << endl;
}

void adminModifyInformation(funcListUser* list, string loggedEmail){
    funcUserNode* current = list->head;
    int option = 0;
    int select;
    system("cls");
    while(current != NULL){
        if(current->email == loggedEmail){
            cout << GREEN << current->name << " | Current User Information\n" << RESET;
            cout << string(50, '-') << endl;
            cout << "Current Information:\n";
            cout << "Name       : " << current->name << endl;
            cout << "Gender     : " << current->gender << endl;
            cout << "Age        : " << current->age << endl;
            cout << "Phone      : " << current->phone << endl;
            cout << "Role       : " << current->role << endl;
            cout << "Email      : " << current->email << endl;
            cout << "Password   : " << current->password << endl;
            cout << string(50, '-') << endl << endl;
            // found = true;
            break;
        }
        current = current->next;
    }    
    do {
        cout << YELLOW << "Update your information:\n" << RESET;
        cout << "1. Update Name\n";
        cout << "2. Update Gender\n";
        cout << "3. Update Age\n";
        cout << "4. Update Phone\n";
        cout << "5. Update Role\n";
        cout << "6. Update Email\n";
        cout << "7. Update Password\n";
        cout << "8. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> option;

        switch(option) {
            case 1: system("cls"); current->name = funcNameMod(current->name); break;
            case 2: system("cls"); current->gender = funcGenderMod(current->gender); break;
            case 3: system("cls"); current->age = funcAgeMod(current->age); break;
            case 4: system("cls"); current->phone = funcPhoneMod(current->phone); break;
            case 5: system("cls"); current->role = funcRoleMod(current->role); break;
            case 6: system("cls"); current->email = funcEmailMod(current->email); break;
            case 7: system("cls"); current->password = funcPasswordMod(current->password); break;
            case 8: system("cls"); cout << YELLOW << "Returning to the previous menu..." << RESET << endl; system("pause"); return; // exit update menu
            default: cout << RED << "Invalid option! Please try again.\n" << RESET; break;
        }

        funcUpdateUserToList(list, select, current->name, current->age, current->gender, current->phone, current->role, current->email, current->password);

        char choice = 'P';
        while(choice != 'Y' && choice != 'N') {
            cout << "Do you want modify something else? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            switch(choice){
                case 'Y': system("cls"); cout << GREEN << "The information has been changed successfully\n" << RESET << endl; break;
                case 'N': system("cls"); funcSaveUsers(list, "Database/users.csv"); return;
                default: cout << RED << "Invalid choice! Please enter Y or N.\n" << RESET << endl;
            }
        }

    } while(option != 8);
}