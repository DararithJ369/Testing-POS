#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cctype>
#include "color.h"
// #include "function.h"
#include "user.h"
#include "product.h"
using namespace std;

void funcUserManagementMenu(funcListUser* userList) {
    funcLoadUsers(userList, "Database/users.csv"); 
    while (true) {
        system("cls");
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << BOLD << YELLOW << "User Management" << RESET << endl;
        cout << "   1. Add user\n   2. Delete user based on email\n   3. Update information\n   4. Search based on email\n   5. Display users\n   6. Back\n";
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        string name, email, password, phone, role;
        char gender;
        int age;
        switch (choice) {
            case 1: {
                addNewUsers(userList);
                cout << GREEN << "New user has been added successfully!" << RESET << endl;
                break;
            }
            case 2:{
                funcDeleteUserByEmail(userList);
                cout << GREEN << "User deleted successfully!" << RESET << endl;
                break;
            }
            case 3: {
                funcUpdateUserToCSV(userList);
                cout << GREEN << "User updated successfully!" << RESET << endl;
                break;
            }
            case 4: {
                funcSearchUserByEmail(userList);
                break;
            }
            case 5: {
                funcDisplayUsers(userList, 1);
                break;
            }
            case 6: {
                return; // Back to main menu
            }
        }
    }
}

void productInventory(funcListProduct* productList){ 
    while(true){
        displayAllProducts(productList, false);
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << BOLD << YELLOW << "Inventory management" << RESET << endl;
        cout << "   1. Add new product\n   2. Modify product\n   3. Short product\n   4. Search product\n   5. Delete product\n   6. Back\n";
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input 
        switch(choice){
            case 1:{
                system("cls");
                addNewProduct(productList);
                break;
            }
            case 2:{
                system("cls");
                modifyProduct(productList);
                break;
            }
            case 3:{
                system("cls");
                sortProducts(productList);
                break;
            }
            case 4:{
                system("cls");
                searchProduct(productList);
                cout << GREEN << "Product sorted successfully!" << RESET << endl;
                break;
            }
            case 5:{
                system("cls");
                deleteProductByID(productList);
                break;
            }
            case 6:{
                cout << YELLOW << "\n\nReturning to the previous menu..." << RESET << endl;
                return;
            }
            default:{
                system("cls");
                cout << RED << "Invalid input! Please try again." << RESET << endl;
                break;
            }
        }
    }
    
}

void adminMenu() {
    string user_email = catchEmailFromTemporaryEmail();
    funcListUser* userList = createfuncListUser();
    funcListProduct* productList = createfuncListProduct();
    loadAllProductsFromCSV(productList, "Database/products.csv");
    while (true) {
        system("cls");
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << "Your current role: " << RED << "admin" << RESET << endl;
        cout << "   1. View inventory\n   2. View user information\n   3. Check log in\n   4. Back\n";
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: productInventory(productList); break;
            // case 2: funcProductManagementMenu(productList); break; // Assuming this function is defined
            case 3: return; // Back to main m=enu
            default: cout << RED << "Invalid option! Please try again." << RESET << endl; break;
        }
    }
}