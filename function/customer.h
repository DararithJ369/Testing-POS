#pragma once
#include <iostream>
#include <string>
#include "storage.h"  // Assume this handles product storage/display/find
using namespace std;


// Cart node structure (doubly linked list)
struct CartNode {
    string productName;
    int quantity;
    CartNode* next;
    CartNode* prev;
};

CartNode* cartHead = nullptr;  // head of cart list

// Add product to cart (push to head)
void addToCart(const string& product, int qty) {
    CartNode* newNode = new CartNode{product, qty, nullptr, nullptr};
    if (cartHead == nullptr) {
        cartHead = newNode;
    } else {
        newNode->next = cartHead;
        cartHead->prev = newNode;
        cartHead = newNode;
    }
    cout << qty << " " << product << "(s) added to your cart.\n";
}

// Remove last added product from cart (pop from head)
void removeFromCart() {
    if (cartHead == nullptr) {
        cout << "Cart is empty, nothing to remove.\n";
        return;
    }
    CartNode* temp = cartHead;
    cout << "Removed " << temp->quantity << " " << temp->productName << "(s) from cart.\n";
    cartHead = cartHead->next;
    if (cartHead != nullptr) {
        cartHead->prev = nullptr;
    }
    delete temp;
}

// Display all products in the cart
void displayCart() {
    if (cartHead == nullptr) {
        cout << "Your cart is empty.\n";
        return;
    }
    cout << "Products in your cart:\n";
    CartNode* current = cartHead;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->productName << " - Quantity: " << current->quantity << "\n";
        current = current->next;
        count++;
    }
}

// Clear entire cart (free all nodes)
void clearCart() {
    while (cartHead != nullptr) {
        removeFromCart();
    }
    cout << "Cart has been cleared.\n";
}

// Checkout simulation
void checkout() {
    cout << "\nCheckout summary:\n";
    displayCart();
    cout << "Thank you for your purchase!\n";
    clearCart();
}

// Sort menu (calls assumed functions from storage.h)
void sortProductsMenu() {
    system("cls");
    int choice;
    while (true) {
        cout << "\nSort products by:\n";
        cout << "1. Alphabet\n2. Category\n3. Price\n4. Back\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: system("cls"); sortStorageByName(); break;
            case 2: system("cls"); sortStorageByCategory(); break;
            case 3: system("cls"); sortStorageByPrice(); break;
            case 4: system("cls"); return;
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
}

// Customer menu
void customerMenu() {
    while (true) {
        int choice;
        cout << "\nCustomer Menu:\n";
        cout << "1. Sort products\n2. Find a product\n3. Shop products\n4. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // Always clear input buffer after cin >>
        switch (choice) {
            case 1: sortProductsMenu(); break;
            case 2: {
                string productName;
                cout << "Enter product name to find: ";
                getline(cin, productName);
                findProduct(productName); // Use improved storage function name
                break;
            }
            case 3: {
                system("cls");
                string productName;
                int quantity;
                while (true) {
                    displayStorage(); // Use improved storage function name
                    cout << "Enter product name to add to cart (type 'stop' to finish): ";
                    getline(cin, productName);
                    if (productName == "stop") break;
                    if (!productExistsByName(productName)) {
                        cout << "Product not found. Try again.\n";
                        continue;
                    }
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cin.ignore();
                    addToCart(productName, quantity);
                }
                checkout();
                char done;
                while (true) {
                    cout << "Are you done buying? (y/n): ";
                    cin >> done;
                    done = tolower(done);
                    cin.ignore();
                    if (done == 'y') {
                        clearCart();
                        return;
                    } else if (done == 'n') {
                        return; // back to customer menu
                    } else {
                        cout << "Invalid choice, try again.\n";
                    }
                }
                break;
            }
            case 4: return;
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
}
