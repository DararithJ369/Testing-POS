#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cctype>
#include "color.h"

using namespace std;

// --- Admin User Struct & List ---

struct Admin_User_Element {
    string name, role, email, password, phone;
    char gender;
    int age;
    Admin_User_Element *next = nullptr, *previous = nullptr;
};

struct Admin_List {
    int size = 0;
    Admin_User_Element *head = nullptr, *tail = nullptr;
};

Admin_List* create_admin_user_list() {
    return new Admin_List;
}

void Admin_insert_user_end(Admin_List* list, string name, char gender, int age, string phone, string role, string email, string password) {
    Admin_User_Element* newnode = new Admin_User_Element{name, role, email, password, phone, gender, age};
    newnode->next = nullptr;
    newnode->previous = list->tail;

    if (list->size == 0) list->head = newnode;
    else list->tail->next = newnode;
    list->tail = newnode;
    list->size++;
}

void admin_delete_by_index(Admin_List* list, int index) {
    if (list->size == 0 || index < 1 || index > list->size) return;
    Admin_User_Element* temp = list->head;
    for (int i = 1; i < index; ++i) temp = temp->next;

    if (temp->previous) temp->previous->next = temp->next;
    else list->head = temp->next;

    if (temp->next) temp->next->previous = temp->previous;
    else list->tail = temp->previous;

    delete temp;
    list->size--;
}

void admin_add_user_at(Admin_List* list, int pos, string name, char gender, int age, string phone, string role, string email, string password) {
    if (pos <= 1 || list->size == 0) {
        Admin_insert_user_end(list, name, gender, age, phone, role, email, password);
        return;
    }
    if (pos > list->size) {
        Admin_insert_user_end(list, name, gender, age, phone, role, email, password);
        return;
    }
    Admin_User_Element* newnode = new Admin_User_Element{name, role, email, password, phone, gender, age};
    Admin_User_Element* current = list->head;
    for (int i = 1; i < pos - 1; ++i) current = current->next;

    newnode->next = current->next;
    newnode->previous = current;
    current->next->previous = newnode;
    current->next = newnode;
    list->size++;
}

void admin_load_users(Admin_List* list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << RED << "Cannot open file!" << RESET << endl; return; }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, ageStr, genderStr, phone, role, email, password;
        getline(ss, name, ','); getline(ss, ageStr, ','); getline(ss, genderStr, ',');
        getline(ss, phone, ','); getline(ss, role, ','); getline(ss, email, ','); getline(ss, password);
        int age = stoi(ageStr);
        char gender = genderStr.empty() ? ' ' : genderStr[0];
        Admin_insert_user_end(list, name, gender, age, phone, role, email, password);
    }
}

void admin_save_users(Admin_List* list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) { cout << RED << "Cannot write to file!" << RESET << endl; return; }
    Admin_User_Element* cur = list->head;
    while (cur) {
        file << cur->name << "," << cur->age << "," << cur->gender << "," << cur->phone << ","
             << cur->role << "," << cur->email << "," << cur->password << "\n";
        cur = cur->next;
    }
}

void admin_display_users(Admin_List* list) {
    cout << left << setw(5) << "No" << setw(20) << "Name" << setw(6) << "Age"
         << setw(8) << "Gender" << setw(15) << "Phone" << setw(12) << "Role" << endl;
    cout << string(66, '-') << endl;

    Admin_User_Element* cur = list->head;
    int no = 1;
    while (cur) {
        cout << setw(5) << no << setw(20) << cur->name << setw(6) << cur->age
             << setw(8) << cur->gender << setw(15) << cur->phone << setw(12) << cur->role << endl;
        cur = cur->next; no++;
    }
}

// Simple validation helpers
bool is_all_alpha(const string& s) { for(char c : s) if(!isalpha(c) && c != ' ') return false; return true; }
bool is_all_digit(const string& s) { for(char c : s) if(!isdigit(c)) return false; return true; }
string to_lower(string s) { for(auto& c : s) c = tolower(c); return s; }

// Simplified input functions (expand if needed)
string input_name() {
    string name; 
    do {
        cout << "Enter name: ";
        getline(cin >> ws, name);
        if (!is_all_alpha(name)) cout << RED << "Invalid name! Try again.\n" << RESET;
    } while (!is_all_alpha(name));
    return name;
}

char input_gender() {
    char g; 
    do {
        cout << "Enter gender (M/F): "; cin >> g;
        g = toupper(g);
        if (g != 'M' && g != 'F') cout << RED << "Invalid gender! Try again.\n" << RESET;
    } while (g != 'M' && g != 'F');
    return g;
}

int input_age() {
    int age;
    do {
        cout << "Enter age: "; cin >> age;
        if (age < 0 || age > 100) cout << RED << "Invalid age! Try again.\n" << RESET;
    } while (age < 0 || age > 100);
    return age;
}

string input_phone() {
    string phone;
    do {
        cout << "Enter phone: "; cin >> phone;
        if (!(is_all_digit(phone) && (phone.size() == 9 || phone.size() == 10) && phone[0] == '0'))
            cout << RED << "Invalid phone! Try again.\n" << RESET;
    } while (!(is_all_digit(phone) && (phone.size() == 9 || phone.size() == 10) && phone[0] == '0'));
    return phone;
}

string input_role() {
    string role;
    while (true) {
        cout << "Enter role (admin, manager, cashier, customer): ";
        cin >> role;
        role = to_lower(role);
        if (role == "admin" || role == "manager" || role == "cashier" || role == "customer")
            return role;
        cout << RED << "Invalid role! Try again.\n" << RESET;
    }
}

// Add new user interactively
void admin_add_user_interactive(Admin_List* list) {
    string name = input_name();
    char gender = input_gender();
    int age = input_age();
    string phone = input_phone();
    string role = input_role();

    string email;
    do {
        cout << "Enter email (must end with @gmail.com): ";
        cin >> email;
        if (email.size() < 10 || email.substr(email.size() - 10) != "@gmail.com") {
            cout << RED << "Invalid email format! Try again.\n" << RESET;
            continue;
        }
        bool exists = false;
        for (auto* cur = list->head; cur != nullptr; cur = cur->next) {
            if (cur->email == email) {
                cout << RED << "Email already used!\n" << RESET;
                exists = true;
                break;
            }
        }
        if (!exists) break;
    } while (true);

    string password;
    cout << "Enter password: ";
    cin >> password;

    Admin_insert_user_end(list, name, gender, age, phone, role, email, password);
    admin_save_users(list, "Database/users.csv");
    cout << GREEN << "User added successfully!\n" << RESET;
}

void adminMenu() {
    Admin_List* list = create_admin_user_list();
    admin_load_users(list, "Database/users.csv");
    while (true) {
        system("cls");
        cout << BOLD << "Admin Menu" << RESET << endl;
        cout << "1. Add User\n2. Delete User\n3. Display Users\n4. Save Users\n5. Load Users\n6. Exit\n";
        cout << "Enter your choice: ";
        int choice; cin >> choice;

        switch (choice) {
            case 1: admin_add_user_interactive(list); break;
            case 2: {
                int index;
                cout << "Enter user index to delete: "; cin >> index;
                admin_delete_by_index(list, index);
                cout << GREEN << "User deleted successfully!\n" << RESET;
                break;
            }
            case 3: admin_display_users(list); system("pause"); break;
            case 4: admin_save_users(list, "Database/users.csv"); break;
            case 5: admin_load_users(list, "Database/users.csv"); break;
            case 6: return; // Exit
            default: cout << RED << "Invalid choice! Try again.\n" << RESET; break;
        }
    }
}
