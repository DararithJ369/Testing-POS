#include<iostream>
#include"include/utils.h"
#include"include/color.h"
#include"include/authentication.h"
#include"include/catch_temporary_user.h"
#include"include/admin.h"
#include"include/customer.h"
#include"include/manager.h"
using namespace std;

int main(){
    
    // Main menu loop
    while (true) {
        int choice;
        cout << "1. Admin Menu\n2. Manager Menu\n3. Customer Menu\n4. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer after cin
        
        switch (choice) {
            case 1: system("cls"); adminMenu(); break;
            case 2: system("cls"); managerMenu(); break;
            case 3: system("cls"); customerMenu(); break;
            case 4: break;
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
}






