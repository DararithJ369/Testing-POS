#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cctype>
#include "color.h"
#include "user.h"
#include "product.h"
#include "storage.h"
using namespace std;

void funcUserManagementMenu(funcListUser* userList) {
    // Load users from CSV file into the userList
    // userList = createfuncuserListUser();
    funcLoadUsers(userList, "Database/users.csv"); // ?
    // funcDisplayUsers(userList);
    cout << GREEN << "Welcome to User Management Menu!" << RESET << endl;
    while (true) {
        system("cls");
        cout << "User Management Menu:\n";
        cout << "1. Add user\n2. Delete user based on email\n3. Update information\n4. Search based on email\n5. Display users\n6. Back\n";
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

void funcProductManagementMenu(funcListProduct* productList) {
    // Load products from CSV file into the productList
    // productList = createfuncListProduct();
    cout << "Loading products from CSV file..." << endl;
    loadAllProductsFromCSV(productList, "Database/products.csv"); // ?
    cout << "Products loaded successfully!" << endl;
    cout << GREEN << "Welcome to Product Management Menu!" << RESET << endl;
    while (true) {
        system("cls");
        cout << "Product Management Menu:\n";
        cout << "1. Add product\n2. Delete product by ID\n3. Update product information\n4. Search product\n5. Display products\n6. Sort product\n7. Back\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                addNewProduct(productList);
                // cout << GREEN << "New product has been added successfully!" << RESET << endl;
                break;
            }
            case 2: {
                deleteProductByID(productList);
                // cout << GREEN << "Product deleted successfully!" << RESET << endl;
                break;
            }
            case 3: {
                modifyProduct(productList);
                // cout << GREEN << "Product updated successfully!" << RESET << endl;
                break;
            }
            case 4: {
                searchProduct(productList);
                break;
            }
            case 5: {
                displayAllProducts(productList, 1);
                break;
            }
            case 6: {
                sortProducts(productList);
                cout << GREEN << "Products sorted successfully!" << RESET << endl;
            }
            default:
                cout << RED << "Invalid option! Please try again." << RESET << endl;
        }
    }
}

void funcAdminMenu() {
    funcListUser* userList = createfuncListUser();
    funcListProduct* productList = createfuncListProduct();
    while (true) {
        system("cls");
        cout << "Admin Menu:\n";
        cout << "1. User Management\n2. Product Management\n3. Back\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: funcUserManagementMenu(userList); break;
            case 2: funcProductManagementMenu(productList); break; // Assuming this function is defined
            case 3: return; // Back to main menu
            default: cout << RED << "Invalid option! Please try again." << RESET << endl; break;
        }
    }
}