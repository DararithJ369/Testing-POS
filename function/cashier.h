#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include "function.h"
using namespace std;

struct Product {
    int productID;
    string productName;
    string category;
    string brand;
    float cost;
    string unit;
    int quantity;
    int quantitySale;
    Product* next;
    Product * previous;
};

struct Stack {
    Product* head;
    Product* tail;
    int size;
};

Stack* CreateEmptyStack() {
    Stack* s = new Stack;
    s->head = nullptr;
    s->tail = nullptr;
    s->size = 0;
    return s;
}

// Add item with new fields
void addItemToCart(Stack* s, int checkID) {
    ifstream inputFile("data.txt");
    if (!inputFile) {
        cout << "Cannot open file: " << endl;
        return;
    }

    string line;
    getline(inputFile, line);

    bool found = false;
    while (getline(inputFile, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string temp;

        Product* t = new Product;

        getline(ss, temp, ',');
        t->productID = stoi(temp);
        if (t->productID == checkID)
        {
            getline(ss, t->productName, ',');
            getline(ss, t->category, ',');
            getline(ss, t->brand, ',');

            getline(ss, temp, ',');
            t->cost = stof(temp);
            getline(ss, t->unit,',');
            getline(ss, temp);
            t->quantity = stoi(temp);

            cout<<"Product found "<<endl;
            cout << "Available quantity: " << t->quantity << "\n";
            cout<<"Enter quantity : ";
            cin>>t->quantitySale;

            if (t->quantitySale > t->quantity) {
                cout << "Not enough stock! Available: " << t->quantity << endl;
                delete t;
                found = true;
                break;
            }
            t->previous = nullptr;
            t->next = nullptr;
            if (s->head == nullptr) {
                s->head = s->tail = t;
            } else {
                t->next = s->head;
                s->head->previous = t;
                s->head = t;
            }
            s->size++;

            ofstream file("history.txt", ios::app);  
            if (!file) {
                cout << "Failed to open file: " <<endl;
                return;
            }else {
                // Write the product sales info to file, tab-separated or CSV as you like
                file << t->productID << ','
                    << t->productName << ','
                    << t->category << ','
                    << t->brand << ','
                    << t->cost << ','
                    << t->unit << ','
                    << t->quantitySale << "\n";
            }
            file.close();
            found = true;
            break;
        }else{
            delete t;
        }
    }
    if (!found) {
        cout << "Product ID " << checkID << " not found in stock." << endl;
    }
    inputFile.close();
}

void updateStock(Stack* s,int checkID) {
    if (s == nullptr || s->size == 0) {
        cout << "No sales data to update." << endl;
        return;
    }
    ifstream inFile("Database/storage.csv");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Failed to open files!" << endl;
        return;
    }
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);

        string temp;
        // int updateID;
        int tempID,tempQuantity;
        string tempName, tempCategory, tempBrand;
        float tempCost;
        string tempUnit;
        try {
            getline(ss, temp, ',');
            tempID = stoi(temp);

            getline(ss, tempName, ',');
            getline(ss, tempCategory, ',');
            getline(ss, tempBrand, ',');

            getline(ss, temp, ',');
            tempCost = stof(temp);

            getline(ss, tempUnit, ',');

            getline(ss, temp);
            tempQuantity = stoi(temp);
        } catch (...) {
            outFile << line << "\n"; 
            continue;
        }
        bool lineWritten = false;
        Product* p = s->head;
        while (p!=nullptr)
        {
            if (checkID == tempID && tempID == p->productID) {
                if (tempQuantity >= p->quantitySale) {
                    tempQuantity -= p->quantitySale;  // Update quantity
                    // cout << "Updated productID " << tempName << " quantity to " << tempQuantity << endl;
                    found = true; 

                    outFile << tempID << "," << tempName << "," << tempCategory << "," << tempBrand<< "," 
                 << tempCost << "," <<tempUnit << "," << tempQuantity << "\n";
                    lineWritten = true;
                } else {
                    cout << "Not enough stock for productID " << tempID << endl;
                    outFile << line << "\n";  // Write original line, no 
                    found = true;
                    // break;
                }
                lineWritten = true;
                break;
            }
            p = p->next;
        }
        if (!lineWritten) {
            // This line does not need to be updated, write as is
            outFile << line << "\n";
        }
    }
    inFile.close();
    outFile.close();

    if (!found) {
        cout << "No matching product found in stock." << endl;
        remove("temp.txt");
        return;
    }
    // Replace original file with temp file
    if (remove("Database/storage.csv") != 0) {
        cout << "Error deleting original file!" << endl;
        return;
    }
    if (rename("temp.txt", "Database/storage.csv") != 0) {
        cout << "Error renaming temp file!" << endl;
        return;
    }
    cout << "Stock updated successfully in Database/storage.csv" << endl;
}

void removeItemFromCart(Stack* s, int ID) {
    Product* e = s->head;
    while (e != nullptr) {
        if (e->productID == ID) {
            cout << "Removing product with ID " << e->productID << " from cart." << endl;
            
            // Remove node from linked list
            if (e->previous != nullptr)
                e->previous->next = e->next;
            else
                s->head = e->next;

            if (e->next != nullptr)
                e->next->previous = e->previous;
            else
                s->tail = e->previous;

            delete e;
            s->size--;

            // Rewrite history.txt to reflect updated cart
            ofstream outFile("history.txt", ios::out);
            if (!outFile) {
                cout << "Failed to open history.txt for writing." << endl;
                return;
            }

            Product* current = s->head;
            while (current != nullptr) {
                outFile << current->productID << ','
                        << current->productName << ','
                        << current->category << ','
                        << current->brand << ','
                        << current->cost << ','
                        << current->unit << ','
                        << current->quantitySale << "\n";
                current = current->next;
            }
            outFile.close();
            return;
        }
        e = e->next;
    }
    cout << "Product with ID " << ID << " not found in cart." << endl;
}
// View products in cart
void viewProduct(Stack* s) {
    if (s->size == 0) {
        cout << "Cart is empty." << endl;
        return;
    }
    cout << "=============================== CART ITEMS ===============================" << endl;
    cout << "No.\tID\tName\t\tBrand\t\tQty\tUnit Price\t|" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    int count = 1;
    Product* e = s->head;
    float total = 0.0;
    while (e != nullptr) {
        // float totalPrice = e->cost * e->quantity;
        cout << count++ << "\t" << e->productID << "\t" << e->productName << "\t\t" << e->brand << "\t\t"
             << e->quantitySale << "\t$" << e->cost  << "\t\t|" << endl;
        total = e->cost * e->quantitySale; 
        e = e->next;
        
    }
    cout << "==========================================================================" << endl;
    cout << "Total items in cart: " << s->size << endl;
    cout <<"Total cost: $" << total << endl;
    cout << "=========================================================================" << endl;

}

// Calculate total cost
float calculateTotal(Stack* s) {
    float total = 0.0;
    double percentage = 100;
    Product* e = s->head;
    while (e != nullptr) {
        total += e->cost * e->quantitySale * (percentage / 100.0);
        e = e->next;
    }
    return total;
}
// Apply discount and print results
void applyDiscount(Stack* s, double percentage,int ID) {
    float total = 0.0;
    Product* e = s->head;
    while (e != nullptr) {
        if (e->productID == ID) {
            total += e->cost * e->quantitySale * (percentage / 100.0);
            e = e->next;
            break; // Skip products not matching the ID
        }
    }
    float discountAmount = total * (percentage / 100.0);
    float finalPrice = total - discountAmount;
    cout << "Total before discount: $" << total << endl;
    cout << "Discount applied (" << percentage << "%): $" << discountAmount << endl;
    cout << "Total after discount: $" << finalPrice << endl;
}

// Process payment
bool processPayment(Stack* s, double paymentAmount) {
    double total = calculateTotal(s);
    if (paymentAmount < total) {
        cout << "Payment not successful. Please try again." << endl;
        return false;
    } else {
        cout << "Payment Successful! Change: $" << paymentAmount - total << endl;
        return true;
    }
}

// Print receipt
void printReceipt(Stack* s) {
    cout << "------------------ RECEIPT ------------------" << endl;
    time_t now = time(0);
    tm* ltm = localtime(&now);

    cout << "Date: " << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-"
         << ltm->tm_mday << endl;

    cout << "Time: " << ltm->tm_hour << ":"
         << ltm->tm_min << ":"
         << ltm->tm_sec << endl << endl;

    Product* e = s->head;
    int count = 1;
    float total = 0;
    while (e != nullptr) {
        float lineTotal = 0.0;
        cout << count++ << ". " << e->productName << " (" << e->brand << ") "
             << "Qty: " << e->quantity << " @ $" << e->cost << " = $" << e->cost * e->quantity<< endl;
        lineTotal += e->cost * e->quantity;
        e = e->next;
    }
    cout << "\nTotal: $" << total << endl;
    cout << "---------------------------------------------" << endl;
}

// Search product by ID
bool searchProduct(Stack* s, int ID) {
    Product* e = s->head;
    while (e != nullptr) {
        if (e->productID == ID) {
            cout << "Product found: " << e->productName << " (" << e->brand << "), Quantity: " << e->quantity << endl;
            return true;
        }
        e = e->next;
    }
    cout << "Product with ID " << e->productID << " not found." << endl;
    return false;
}

// Cancel transaction (clear cart)
void cancelTransaction(Stack* s) {
    Product* e = s->head;
    while (e != nullptr) {
        Product* temp = e;
        e = e->next;
        delete temp;
    }
    s->head = nullptr;
    s->tail = nullptr;
    s->size = 0;
    cout << "Transaction cancelled. Cart is empty." << endl;

}
// processSales
void viewTransaction(Stack*s){
    ifstream file("history.txt");
    if (!file) {
        cout << "Cannot open history file: "  << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;

        Product* p = new Product;

        try {
            // Parse each CSV field
            getline(ss, temp, ',');
            p->productID = stoi(temp);

            getline(ss, p->productName, ',');
            getline(ss, p->category, ',');
            getline(ss, p->brand, ',');

            getline(ss, temp, ',');
            p->cost = stof(temp);

            getline(ss, p->unit, ',');

            getline(ss, temp);
            p->quantitySale = stoi(temp);
        } catch (...) {
            cout << "Error parsing line, skipping: " << line << endl;
            delete p;
            continue;
        }

        // Insert at the end of the doubly linked list
        p->next = nullptr;
        p->previous = s->tail;

        if (s->tail != nullptr) {
            s->tail->next = p;
        } else {
            s->head = p; // first element
        }
        s->tail = p;
        s->size++;
    }

    file.close();
    cout << "Loaded " << s->size << " records from " << "history.txt" << endl;
}




void cashierMenu(){
    Stack * s = CreateEmptyStack();
    int num,quantity,ID;
    float total;
    double percentage,cost;
    string product,brand;
    cout<<"Hello cashier!!!"<<endl;
    int n;
    do
    {
        cout<<"Option to use have :"<<endl;
        cout<<"\033[1;33m-----------------------------------------------------------------\033[0m"<<endl;
        cout<<"\033[1;33m|1.ADD ITEM\t\t\t\t2.REMOVE ITEM\t\t|\n|3.VIEW ITEM\t\t\t\t4.CALCULATE TOTAL\t|\n|5.APPLY DISCOUNT\t\t\t6.PROCESS PAYMENT\t|\n|7.PRINT RECEIPT\t\t\t8.SEARCH PRODUCT\t|\n|9.CANCEL\t\t\t\t10.VIEW TRANSACTION|\033[0m"<<endl;
        cout<<"\033[1;33m-----------------------------------------------------------------\033[0m"<<endl;
        cout<<"Enter number :"; cin>>num;
        switch (num)
        {
        case 1:
        // work
            cout<<"\033[34m-------------ADD ITEM------------------\033[0m"<<endl;
            cout << "Enter product ID : "; cin>> ID;
            addItemToCart(s,ID);
            updateStock(s,ID);
            break;
        case 2:
        // work
            cout<<"\033[34m-------------REMOVE ITEM------------------\033[0m"<<endl;
            cout << "Enter product ID to remove: "; cin >> ID;
            removeItemFromCart(s,ID);
            break;
        case 3:
        // work
            cout<<"\033[34m-------------VIEW ITEM------------------\033[0m"<<endl;
            cout << "View item in cart..." << endl;
            viewProduct(s);
            break;
        case 4:
            // work
            cout<<"\033[34m-------------CALCULATE TOTAL------------------\033[0m"<<endl;
            cout << "Calculating total..." << endl;
            total = calculateTotal(s);
            cout<<"Total cost: $" << total << endl;
            // when calculate iterm it save to the history
            break;
        case 5:
        // work
            cout<<"\033[34m-------------APPLY DISCOUNT------------------\033[0m"<<endl;
            cout << "Enter discount percentage: "; cin >> percentage;
            cout << "Enter product ID for discount: "; cin >> ID;
            applyDiscount(s,percentage,ID);
            break;
        case 6:
            cout<<"\033[34m-------------PROCESS PAYMENT------------------\033[0m"<<endl;
            cout << "Enter payment amount: "; cin >> percentage;
            processPayment(s,percentage);
            break;
        case 7:
        // work
            cout<<"\033[34m-------------PRINT RECEIPT------------------\033[0m"<<endl;
            cout << "Printing receipt..." << endl;
            // this_thread::sleep_for(chrono::seconds(5));
            printReceipt(s);
            break;
        case 8:
        // work
            cout<<"\033[34m-------------SEARCH PRODUCT------------------\033[0m"<<endl;
            cout<<"Enter product ID: ";
            cin >> ID;
            searchProduct(s,ID);
            break;  
        case 9:
        // work
            cout<<"\033[34m-------------CANCEL------------------\033[0m"<<endl;
            cancelTransaction(s);
            break;
        case 10:
            cout<<"\033[34m-------------VIEW TRANSACTION------------------\033[0m"<<endl;
            viewTransaction(s);
            break;
        default:
            cout << "Invalid option. Please try again."<<endl;
            break;
        } 
    }while (num!=11);
}


