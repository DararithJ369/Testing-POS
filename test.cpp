#include<iostream>
#include <windows.h>
#include "function/user.h"
#include "function/product.h"
// #include "function/storage.h"
// #include "function/cashier.h"
#include "function/admin.h"
// #include "function/customer.h"
// #include "function/manager.h"
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
            case 1: funcAdminMenu(); break;
            // case 2: managerMenu(); break;
            // case 3: cashierMenu(); break;
            // case 4: customerMenu(); break;
            // case 5: saveStorageToFile(); return 0; // Save and exit
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
}



