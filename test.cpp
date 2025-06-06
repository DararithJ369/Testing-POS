#include<iostream>
#include"include/catch_temporary_user.h"
#include"include/authentication.h"
#include"include/admin.h"
#include"include/customer.h"
#include"include/manager.h"
#include"include/color.h"
#include"include/utils.h"
using namespace std;

int main(){
    
    // Main menu loop
    while (true) {
        cout << RESET << endl;
        int choice;
        cout << "Main Menu:\n";
        cout << "1. Admin Menu\n2. Manager Menu\n3. Cashier Menu\n4. Customer Menu\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer after cin
        
        switch (choice) {
            case 1: adminMenu(); break;
            // case 2: managerMenu(); break;
            // case 3: cashierMenu(); break;
            case 4: {system("cls");customerMenu(); break;}
            // case 5: saveStorageToFile(); return 0; // Save and exit
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
}






