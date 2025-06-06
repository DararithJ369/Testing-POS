#pragma once
#include <iostream>
#include <string>
#include "color.h"
#include "product.h"
#include "user.h"
// #include "storage.h"  // Assume this handles product storage/display/find
using namespace std;

void selectAllProducts(funcListProduct* list, funcListProduct* cartList){

    while(true){
        int choice;
        displayAllProducts(list, 0);

        cout << CYAN << "\n\n==> Product Selection" << RESET << endl;
        cout << "1. Add item to cart\n2. Remove item from cart\n3. View receipt\n4. Cancel\n5. Check out" << endl;
        calculateReceipt(cartList);
        cout << "Enter your option: "; cin >> choice;
        switch(choice){
            case 1: {
                system("cls");
                string id;
                int qty;    
                funcProductNode* product = NULL;
                do {
                    cout << "Enter ID of product    : "; getline(cin >> ws, id);
                    product = findProductByID(list, id);
                    if(!product) {cout << RED << "Product not found! Please enter valid ID." << RESET << endl;}
                } while(!product);
                cout << GREEN << "Product selected       : " << product->name << RESET << endl;
                cout << "Enter quantity         : "; cin >> qty;
                if(qty > product->stock){
                    cout << RED << "Not enough stock! Only " << GREEN << product->stock << RED << " available." << RESET << endl;
                    system("pause");
                    break;
                }
                addItemToCart(cartList, list, id, qty);
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                string id;
                int choice;
                int qty;
                while(true){
                    printReceipt(cartList, 1); 
                    cout << "Enter ID of product to remove/update quantity: "; getline(cin >> ws, id);
                    funcProductNode* cartProduct = findProductByID(cartList, id);
                    if(cartProduct){
                        cout << "1. Remove item in cart by ID\n2. Update quantity\n3. Back" << endl;
                        cout << "Enter your choice: "; cin >> choice;
                        switch(choice){
                            case 1: {
                                removeItemFromCart(cartList, list, id);
                                system("pause");
                                break;
                            }
                            case 2: {
                                cout << "Enter quantity to update: "; cin >> qty;
                                funcProductNode* cartProduct = findProductByID(cartList, id);
                                funcProductNode* product = findProductByID(list, id);
                                if (!cartProduct || !product) {
                                    cout << RED << "Product not found!" << RESET << endl;
                                    break;
                                }
                                int availableStock = product->stock + cartProduct->productSale; // what’s in stock + what’s already in cart
                                if (qty > availableStock) {
                                    cout << RED << "Not enough stock! Only " << GREEN << availableStock << RED << " available." << RESET << endl;
                                } else {
                                    // Update stock: return old cart qty to stock, then subtract new qty
                                    product->stock = availableStock - qty;
                                    cartProduct->productSale = qty;
                                    cout << GREEN << "Updated quantity for " << cartProduct->name << " (ID: " << id << ") to " << qty << RESET << endl;
                                }
                                system("pause");
                                break;
                            }
                            case 3: {return;}
                            default: { cout << RED << "Invalid input!!!" << RESET << endl; break;}
                        }
                        break;
                    }
                    else {cout << RED << "Product not found in cart!" << RESET << endl;}
                }

                break;
            }
            case 3: {
                system("cls");
                printReceipt(cartList, 1);
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << YELLOW << "Returning to previous menu..." << RESET << endl;
                system("pause");
                system("cls");
                return;
            }
            case 5: {
                system("cls");
                checkout(cartList);
                saveAllProductsToCSV(list, "Database/products.csv");
                return;
            }
            default: {
                cout << RED << "Invalid option! Please try again." << RESET << endl;
                system("cls");
                break;
            }
        }
    }

}

void helpForCustomer(){
    cout << BLUE <<"Select Product" << RESET << " : Use for process your sales(Add item to cart, Remove item from cart, View cart and Checkout)." << endl;
    cout << BLUE << "Check Your Information" << RESET << " : Check/Edit your own information (Name, age, gender, Phone Number, Role, Email, Password)" << endl;
    cout << BLUE << "Any help from our system" << RESET << " : Use to check the detail of any option." << endl;
    cout << BLUE << "Exit our program" << RESET << " : Exit the whole program." << endl;
}


void customerMenu(){
    int choice;
    funcListUser* userList = createfuncListUser();
    funcListProduct* cartList = createfuncListProduct();
    funcListProduct* list = createfuncListProduct();
    loadAllProductsFromCSV(list, "Database/products.csv");
    funcLoadUsers(userList, "Database/users.csv");
    string loggedEmail = catchEmailFromTemporaryEmail();
    while(true){
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << "Your current role: " << YELLOW << "customer" << RESET << endl;
        cout << "   1. Select Product\n   2. Check your information\n   3. Any help from our system\n   4. Back" << endl;
        cout << BOLD << GRAY << string(50, '-') << RESET << endl;
        cout << "Enter your option: ", cin >> choice;
        switch(choice){
            case 1: {system("cls"); selectAllProducts(list, cartList); break;}
            case 2: {
                // char ch;
                system("cls"); 
                funcModifyOwnInfo(userList, loggedEmail);
                break;
            }
            case 3: {
                system("cls");
                helpForCustomer();
                system("pause");
                break;
            }
            case 4: {
                cout << endl;
                cout << YELLOW << "Returning to previous menu." << RESET << endl;
                string currentEmail = catchEmailFromTemporaryEmail();
                logUserAction(currentEmail, "Exited");
                system("pause");
                return;
            }
            default: {
                cout << RED << "Invalid Input !!! Please Try Again." << RESET << endl;
                break;
            }
        }
    }
}


