#include <iostream>
#include "color.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include "storage.h"
using namespace std;

struct funcProductNode{
    string id, name, category, brand, unit;
    double price;
    int stock;
    int productSale;
    double discount; // New field for discount percentage
    funcProductNode* next;
    funcProductNode* prev;
};

struct funcListProduct{
    int size;
    funcProductNode* head;
    funcProductNode* tail;
};

funcListProduct* createfuncListProduct() {
    funcListProduct* list = new funcListProduct;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

string prodCapitalization(string index){
    string cap;
    bool isFirst = true;
    for(char c : index){
        if(isFirst){cap += toupper(c); isFirst = false;}
        else if(c == ' '){cap += c; isFirst = true;}
        else cap += c;
    }
    return cap;
}

void addProductBegin(funcListProduct* list, string id, string name, string category, string brand, double price, string unit, int stock, double discount) {
    funcProductNode* newNode = new funcProductNode;
    newNode->id = id;
    newNode->name = name;
    newNode->category = category;
    newNode->brand = brand;
    newNode->price = price;
    newNode->unit = unit; // Add unit field
    newNode->stock = stock;
    newNode->discount = discount; // Set the discount percentage
    newNode->next = list->head;
    newNode->prev = NULL;
    if (list->head != NULL) list->head->prev = newNode;
    else list->tail = newNode;
    list->head = newNode;
    list->size++;
}

void addProductEnd(funcListProduct* list, string id, string name, string category, string brand, double price, string unit, int stock, double discount) {
    funcProductNode* newNode = new funcProductNode;
    newNode->id = id;
    newNode->name = name;
    newNode->category = category;
    newNode->brand = brand;
    newNode->price = price;
    newNode->unit = unit; // Add unit field
    newNode->stock = stock;
    newNode->discount = discount; // Set the discount percentage
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (list->tail != NULL) list->tail->next = newNode;
    else list->head = newNode;
    list->tail = newNode;
    list->size++;
}

void addProductAt(funcListProduct* list, int pos, string id, string name, string category, string brand, double price, string unit, int stock, double discount) {
    funcProductNode* newNode = new funcProductNode;
    newNode->id = id;
    newNode->name = name;
    newNode->category = category;
    newNode->brand = brand;
    newNode->price = price;
    newNode->unit = unit; // Add unit field
    newNode->stock = stock;
    newNode->productSale = 0; // Initialize productSale to 0
    newNode->discount = discount; // Set the discount percentage
    if(pos == 1|| list->size == 0) addProductBegin(list, id, name, category, brand, price, unit, stock, discount);
    else if(pos > list->size) addProductEnd(list, id, name, category, brand, price, unit, stock, discount);
    else {
        funcProductNode* current = list->head;
        for(int i = 1; i < pos - 1 && current != NULL; i++) {current = current->next;}
        newNode->next = current->next;
        newNode->prev = current;
        if(current->next != NULL) current->next->prev = newNode;
        current->next = newNode;
        list->size++;
    }
}

void deleteProductBegin(funcListProduct* list) {
    if (list->head == NULL) return; // List is empty
    funcProductNode* temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) list->head->prev = NULL;
    else list->tail = NULL; // If the list becomes empty
    delete temp;
    list->size--;
}

void deleteProductEnd(funcListProduct* list) {
    if (list->tail == NULL) return; // List is empty
    funcProductNode* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) list->tail->next = NULL;
    else list->head = NULL; // If the list becomes empty
    delete temp;
    list->size--;
}

void deleteProductAt(funcListProduct* list, int pos){
    if(list->size == 0 || pos < 0) return; // Invalid position
    if(pos == list->size) deleteProductEnd(list);
    else if(pos == 1) deleteProductBegin(list);
    else {
        funcProductNode* current = list->head;
        for(int i = 1; i < pos; i++) {current = current->next;}
        if(current->prev != NULL) current->prev->next = current->next;
        else list->head = current->next; // If deleting head
        if(current->next != NULL) current->next->prev = current->prev;
        else list->tail = current->prev; // If deleting tail
        delete current;
        list->size--;
    }
}

void loadAllProductsFromCSV(funcListProduct* list, string filename) {
    ifstream file(filename, ios::in);
    if(!file.is_open()) {cout << "Error opening file: " << filename << endl; return;}
    string line;
    getline(file, line); // Skip header line if exists
    while(getline(file, line)){
        stringstream ss(line);
        string id, name, category, brand, priceStr, unit, stockStr, disStr;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, brand, ',');
        getline(ss, priceStr, ',');
        getline(ss, unit, ',');
        getline(ss, stockStr, ',');
        getline(ss, disStr, ',');
        double price = stod(priceStr);
        int stock = stoi(stockStr);
        double discount = stod(disStr);
        addProductEnd(list, id, name, category, brand, price, unit, stock, discount);
    }
    file.close();
}

void saveAllProductsToCSV(funcListProduct* list, string filename) {
    ofstream file;
    file.open(filename, ios::out | ios::trunc);
    if(!file.is_open()) {cout << "Error opening file: " << filename << endl; return;}
    funcProductNode* current = list->head;
    int count = 1;
    file << "ID,Name,Category,Brand,Price,Unit,Stock,Discount" << endl; // Header
    while(current != NULL) {
        current->id = to_string(count); // Assign ID based on position
        file << current->id << ","
             << current->name << ","
             << current->category << ","
             << current->brand << ","
             << fixed << setprecision(2) << current->price << ","
             << current->unit << ","
             << current->stock << ","
             << fixed << setprecision(2) << current->discount * 100.0 // Save discount as percentage
             << endl;
        current = current->next;
        count++;
    }
    file.close();
}

void displayAllProducts(funcListProduct* list, bool check){
    funcProductNode* current = list->head;
    cout << VIOLET << "All Products in Stock" << RESET << endl;
    cout << string(105, '-') << endl;
    cout << left << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(18) << "Category" 
         << setw(15) << "Brand" 
         << setw(10) << "Price" 
         << setw(10) << "Stock" 
         << setw(10) << "Unit" 
         << setw(10) << "Discount" 
         << endl;
    cout << string(105, '-') << endl;
    while(current != NULL) {
        cout << left << setw(10) << current->id 
             << setw(20) << current->name 
             << setw(18) << current->category 
             << setw(15) << current->brand 
             << setw(10) << fixed << setprecision(2) << current->price 
             << setw(10) << current->stock 
             << setw(10) << current->unit 
             << setw(10) << fixed << setprecision(2) << current->discount * 105.0 
             << "%" << endl;
        if(check && current->stock <= 0) {
            cout << RED << "Product " << current->name << " is out of stock!" << RESET << endl;
        }
        current = current->next;
    }
    cout << string(105, '-') << endl;
    cout << YELLOW << "Total Products: " << list->size << RESET << endl;
    if(check){system("pause"); system("cls");}
}

bool isValidCategory(string category) {
    string arr[] = {"Fruit", "Meat", "Electronics", "Canned", "Bakery", "Vegetable", "Dairy", "Snacks", "Household", "Beverage", "Dessert", "Personal Care", "Stationery", "Baking", "Breakfast", "Condiment", "Grains", "Nutrition", "Meat Alternative"};
    for(string cat : arr){if(cat == category)   return true;}
    return false;
}

void addNewProduct(funcListProduct* list) {
    system("cls");
    funcProductNode Product;
    funcProductNode* current;
    cout << VIOLET << "Add New Product" << RESET << endl;
    cout << string(90, '-') << endl;
    cout << "Please enter the following product information to at new product\n";
    cout << string(90, '-') << endl;
    cout << "Product Name:      "; getline(cin >> ws, Product.name);
    Product.name = prodCapitalization(Product.name);
    Product.id = to_string(list->size + 1); // Assign ID based on current size
    system("cls");
    while(true){
        cout << YELLOW << "Attention: " << RESET << "Please enter the right category." << endl;
        cout << YELLOW << "Available categories: " << RESET << "{Fruit, Meat, Electronics, Canned, Bakery, Vegetable, Dairy, Snacks, Household, Beverage, Dessert, Personal Care, Stationery, Baking, Breakfast, Condiment, Grains, Nutrition, Meat Alternative}" << endl;
        cout << "Product Category:  "; getline(cin >> ws, Product.category);
        Product.category = prodCapitalization(Product.category);
        system("cls");
        if(isValidCategory(Product.category)) break;
        else cout << RED << "Invalid category! Please enter a valid category." << RESET << endl;
    }

    cout << VIOLET << "Add New Product" << RESET << endl;
    cout << string(90, '-') << endl;
    cout << "Please enter the following product information to at new product\n";
    cout << string(90, '-') << endl;
    cout << "Product Name:      " << Product.name << endl;
    cout << "Product ID:        " << Product.id << endl;
    cout << "Product Category:  " << Product.category << endl;
    cout << "Product Brand:     "; getline(cin >> ws, Product.brand);
    system("cls");
    Product.brand = prodCapitalization(Product.brand);
    cout << VIOLET << "Add New Product" << RESET << endl;
    cout << string(90, '-') << endl;
    cout << "Please enter the following product information to at new product\n";
    cout << string(90, '-') << endl;
    cout << "Product Name:      " << Product.name << endl;
    cout << "Product ID:        " << Product.id << endl;
    cout << "Product Category:  " << Product.category << endl;
    cout << "Product Brand:     " << Product.brand << endl;
    cout << "Product Price:     "; cin >> Product.price;
    cout << "Product Unit:      "; getline(cin >> ws, Product.unit);
    cout << "Product Stock:     "; cin >> Product.stock;
    cout << "Product Discount:  "; cin >> Product.discount;
    Product.discount /= 100.0; // Store discount as a fraction
    system("cls");
    cout << VIOLET << "Add New Product" << RESET << endl;
    cout << string(90, '-') << endl;
    cout << "Please enter the following product information to at new product\n";
    cout << string(90, '-') << endl;
    cout << "Product Name:      " << Product.name << endl;
    cout << "Product ID:        " << Product.id << endl;
    cout << "Product Category:  " << Product.category << endl;
    cout << "Product Brand:     " << Product.brand << endl;
    cout << "Product Price:     " << fixed << setprecision(2) << Product.price << endl;
    cout << "Product Unit:      " << Product.unit << endl;
    cout << "Product Stock:     " << Product.stock << endl;
    cout << "Product Discount:  " << fixed << setprecision(2) << Product.discount * 100.0 << "%" << endl;
    addProductEnd(list, Product.id, Product.name, Product.category, Product.brand, Product.price, Product.unit, Product.stock, Product.discount);
    saveAllProductsToCSV(list, "Database/products.csv");
    system("cls");
    cout << GREEN << "New product has been added successfully!" << RESET << endl;
    system("pause"); 
}

void deleteProductByID(funcListProduct* list) {
    system("cls");
    string id;
    displayAllProducts(list, false);
    cout << endl;
    cout << "Please enter the product ID to delete: "; getline(cin >> ws, id);
    system("cls");
    funcProductNode* current = list->head;
    bool found = false;
    while(current != NULL) {
        if(current->id == id) found = true;
        current = current->next;
    }
    if(!found) cout << RED << "Product with ID " << id << " not found!" << RESET << endl;
    else {
        int idToDelete = stoi(id);
        deleteProductAt(list, idToDelete);
        cout << GREEN << "Product with ID " << id << " has been deleted successfully!" << RESET << endl;
        saveAllProductsToCSV(list, "Database/products.csv");
    }
    system("pause");
    system("cls");
}

void displayProductsByCategory(funcListProduct* list, bool check) {
    string category;
    cout << "Enter the category to display products: ";
    cin.ignore();
    getline(cin, category);
    category = prodCapitalization(category);
    int count = 0;
    system("cls");
    funcProductNode* current = list->head;
    while(current != NULL){
        if(current->category == category) count++;
        current = current->next;
    }
    if(count == 0) cout << RED << "No products found in category: " << category << RESET << endl;
    else{
        current = list->head;
        cout << VIOLET << "Products in Category: " << category << RESET << endl;
        cout << string(90, '-') << endl;
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Category" 
             << setw(15) << "Brand" 
             << setw(10) << "Price" 
             << setw(10) << "Stock" 
             << setw(10) << "Sale" 
             << setw(10) << "Discount" 
             << endl;
        cout << string(90, '-') << endl;
        while(current != NULL) {
            if(current->category == category) {
                cout << left << setw(10) << current->id 
                     << setw(20) << current->name 
                     << setw(15) << current->category 
                     << setw(15) << current->brand 
                     << setw(10) << fixed << setprecision(2) << current->price 
                     << setw(10) << current->stock 
                     << setw(10) << current->productSale 
                     << setw(10) << fixed << setprecision(2) << current->discount * 105.0 
                     << "%" << endl;
            }
            current = current->next;
        }
        cout << string(90, '-') << endl;
        cout << YELLOW << "Total Products in Category: " << count << RESET << endl;
    } 
    if(check){system("pause"); system("cls");}
}

void displayProductsByBrand(funcListProduct* list, bool check) {
    string brand;
    cout << "Enter the brand to display products: ";
    cin.ignore();
    getline(cin, brand);
    brand = prodCapitalization(brand);
    int count = 0;
    system("cls");
    funcProductNode* current = list->head;
    while(current != NULL){
        if(current->brand == brand) count++;
        current = current->next;
    }
    if(count == 0) cout << RED << "No products found for brand: " << brand << RESET << endl;
    else{
        current = list->head;
        cout << VIOLET << "Products by Brand: " << brand << RESET << endl;
        cout << string(90, '-') << endl;
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Category" 
             << setw(15) << "Brand" 
             << setw(10) << "Price" 
             << setw(10) << "Stock" 
             << setw(10) << "Sale" 
             << setw(10) << "Discount" 
             << endl;
        cout << string(90, '-') << endl;
        while(current != NULL) {
            if(current->brand == brand) {
                cout << left << setw(10) << current->id 
                     << setw(20) << current->name 
                     << setw(15) << current->category 
                     << setw(15) << current->brand 
                     << setw(10) << fixed << setprecision(2) << current->price 
                     << setw(10) << current->stock 
                     << setw(10) << current->productSale 
                     << setw(10) << fixed << setprecision(2) << current->discount * 105.0 
                     <<"%"<< endl;
            }
            current = current->next;
        }
        cout<<string(90,'-')<<endl;
        cout<<YELLOW<<"Total Products by Brand: "<<count<<RESET<<endl;
    } 
    if(check){system("pause"); system("cls");}
}

void displayProductsBy(funcListProduct* list){
    int choice;
    while(true){
        cout << "Display products by:" << endl;
        cout << "1. Category" << endl;
        cout << "2. Brand" << endl;
        cout << "3. Display all products" << endl;
        cout << "4. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:system("cls"); displayProductsByCategory(list, 1); break;
            case 2:system("cls"); displayProductsByBrand(list, 1); break;
            case 3:system("cls"); displayAllProducts(list, 1); break;
            case 4:return; // Exit the function
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }
}

void modifyProductName(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    string newName;
    string prevName = current->name;
    cout << "Current name: " << current->name << endl;
    cout << "Enter new name: ";
    getline(cin >> ws, newName);
    newName = prodCapitalization(newName);
    current->name = newName;
    system("cls");
    cout << GREEN << "Product's name updated successfully!" << RESET << endl;
    cout << RED << prevName << " has been changed to " << current->name << RESET << endl;
}

void modifyProductCategory(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    string newCategory;
    string prevCategory = current->category;
    cout << "Current category: " << current->category << endl;
    cout << "Enter new category: ";
    getline(cin >> ws, newCategory);
    newCategory = prodCapitalization(newCategory);
    current->category = newCategory;
    system("cls");
    cout << GREEN << "Product's category updated successfully!" << RESET << endl;
    cout << RED << prevCategory << " has been changed to " << current->category << RESET << endl;
}

void modifyProductBrand(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    string newBrand;
    string prevBrand = current->brand;
    cout << "Current brand: " << current->brand << endl;
    cout << "Enter new brand: ";
    getline(cin >> ws, newBrand);
    newBrand = prodCapitalization(newBrand);
    current->brand = newBrand;
    system("cls");
    cout << GREEN << "Product's brand updated successfully!" << RESET << endl;
    cout << RED << prevBrand << " has been changed to " << current->brand << RESET << endl;
}

void modifyProductPrice(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    double newPrice;
    double prevPrice = current->price;
    cout << "Current price: " << fixed << setprecision(2) << current->price << endl;
    cout << "Enter new price: ";
    cin >> newPrice;
    current->price = newPrice;
    system("cls");
    cout << GREEN << "Product's price updated successfully!" << RESET << endl;
    cout << RED << "Price has been changed from " << fixed << setprecision(2) << prevPrice 
         << " to " << fixed << setprecision(2) << current->price << RESET << endl;
}

void modifyProductUnit(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    string newUnit;
    string prevUnit = current->unit;
    cout << "Current unit: " << current->unit << endl;
    cout << "Enter new unit: ";
    getline(cin >> ws, newUnit);
    current->unit = newUnit;
    system("cls");
    cout << GREEN << "Product's unit updated successfully!" << RESET << endl;
    cout << RED << prevUnit << " has been changed to " << current->unit << RESET << endl;
}

void modifyProductStock(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    int newStock;
    int prevStock = current->stock;
    cout << "Current stock: " << current->stock << endl;
    cout << "Enter new stock: ";
    cin >> newStock;
    current->stock = newStock;
    system("cls");
    cout << GREEN << "Product's stock updated successfully!" << RESET << endl;
    cout << RED << "Stock has been changed from " 
         << prevStock << " to " << current->stock << RESET << endl;
}

void modifyProductDiscount(funcListProduct* list, funcProductNode* current){
    cout << GREEN << current->name << "'s information" << RESET << endl;
    double newDiscount;
    double prevDiscount = current->discount * 105.0; // Convert to percentage
    cout << "Current discount: " << fixed << setprecision(2) << prevDiscount << "%" << endl;
    cout << "Enter new discount (in percentage): ";
    cin >> newDiscount;
    current->discount = newDiscount / 105.0; // Store as a fraction
    system("cls");
    cout << GREEN << "Product's discount updated successfully!" << RESET << endl;
    cout << RED << "Discount has been changed from " 
         << fixed << setprecision(2) << prevDiscount 
         << "% to " << fixed << setprecision(2) 
         << current->discount * 105.0 << "%" << RESET << endl;
}

void modifyProduct(funcListProduct* list) {
    system("cls");
    string enterID;
    cout << VIOLET << "Modify Product Information" << RESET << endl;
    displayAllProducts(list, false);
    cout << endl << endl;
    cout << "Enter Product ID to modify: "; getline(cin >> ws, enterID);
    int pos = stoi(enterID);
    system("cls");
    funcProductNode* current = list->head;
    bool found = false;
    while(current != NULL){
        if(current->id == enterID) found = true; break;
        current = current->next;
    }
    if(!found) cout << RED << "Product with ID " << enterID << " nnot found!" << RESET << endl;
    else{
        cout << GREEN << current->name << "'s information" << RESET << endl;
        cout << "ID: " << current->id << endl;
        cout << "Name: " << current->name << endl;
        cout << "Category: " << current->category << endl;
        cout << "Brand: " << current->brand << endl;
        cout << "Price: " << fixed << setprecision(2) << current->price << endl;
        cout << "Unit: " << current->unit << endl;
        cout << "Stock: " << current->stock << endl;
        cout << "Unit: " << current->unit << endl;
        cout << "Discount: " << fixed << setprecision(2) << current->discount * 105.0 << "%" << endl;
        int choice;
        cout << string(90, '-') << endl;
        cout << "What do you want to modify?" << endl;
        cout << "1. Name" << endl;
        cout << "2. Category" << endl;
        cout << "3. Brand" << endl;
        cout << "4. Price" << endl;
        cout << "5. Unit" << endl;
        cout << "6. Stock" << endl;
        cout << "7. Discount" << endl;
        cout << "8. Back to main menu" << endl;
        cout << "Enter your choice: "; cin >> choice;
        switch(choice){
            case 1:system("cls"); modifyProductName(list, current); break;
            case 2:system("cls"); modifyProductCategory(list, current); break;
            case 3:system("cls"); modifyProductBrand(list, current); break;
            case 4:system("cls"); modifyProductPrice(list, current); break;
            case 5:system("cls"); modifyProductUnit(list, current); break;
            case 6:system("cls"); modifyProductStock(list, current); break;
            case 7:system("cls"); modifyProductDiscount(list, current); break;
            case 8:system("cls"); break;
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl; break;
        }
        string id = current->id;
        string name = current->name;
        string category = current->category;
        string brand = current->brand;
        double price = current->price;
        string unit = current->unit; // Add unit field
        int stock = current->stock;
        double discount = current->discount;
        
        cout << VIOLET << "Revised Product Information" << RESET << endl;
        cout << string(40, '-') << endl;
        cout << "ID:        " << id << endl;
        cout << "Name:      " << name << endl;
        cout << "Category:  " << category << endl;
        cout << "Brand:     " << brand << endl;
        cout << "Price:     " << fixed << setprecision(2) << price << endl;
        cout << "Unit:      " << unit << endl; // Display unit
        cout << "Stock:     " << stock << endl;
        cout << "Discount:  " << fixed << setprecision(2) << discount * 105.0 << "%" << endl;
        cout << string(40, '-') << endl;

        deleteProductAt(list, pos);
        addProductAt(list, pos, id, name, category, brand, price, unit, stock, discount);
        saveAllProductsToCSV(list, "Database/products.csv");
    }
    cout << GREEN << "Product information modified successfully!" << RESET << endl << endl;
    system("pause");
    system("cls");
}

void searchByProductName(funcListProduct* list, bool clearScreen) {
    string name;
    bool check = false;
    cout << "Enter the product name to search: "; getline(cin >> ws, name);
    name = prodCapitalization(name);
    system("cls");
    funcProductNode* current = list->head;
    while(current != NULL){
        if(current->name == name) {check = true; break;}
        current = current->next;
    }
    if(!check) cout << RED << "Product with name " << name << " not found!" << RESET << endl;
    else {
        cout << VIOLET << "Product Information" << RESET << endl;
        cout << string(40, '-') << endl;
        cout << "ID:        " << current->id << endl;
        cout << "Name:      " << current->name << endl;
        cout << "Category:  " << current->category << endl;
        cout << "Brand:     " << current->brand << endl;
        cout << "Price:     " << fixed << setprecision(2) << current->price << endl;
        cout << "Stock:     " << current->stock << endl;
        cout << "Discount:  " << fixed << setprecision(2) << current->discount * 105.0 << "%"<< endl;
        cout << string(40,'-') << endl;
    }
    if(clearScreen) system("pause"); system("cls");   
}

void searchByProductID(funcListProduct* list, bool clearScreen) {
    string id;
    bool check = false;
    cout << "Enter the product ID to search: "; getline(cin >> ws, id);
    system("cls");
    funcProductNode* current = list->head;
    while(current != NULL){
        if(current->id == id) {check = true; break;}
        current = current->next;
    }
    if(!check) cout << RED << "Product with ID " << id << " not found!" << RESET << endl;
    else {
        cout << VIOLET << "Product Information" << RESET << endl;
        cout << string(40, '-') << endl;
        cout << "ID:        " << current->id << endl;
        cout << "Name:      " << current->name << endl;
        cout << "Category:  " << current->category << endl;
        cout << "Brand:     " << current->brand << endl;
        cout << "Price:     " << fixed << setprecision(2) << current->price << endl;
        cout << "Stock:     " << current->stock << endl;
        cout << "Discount:  " << fixed << setprecision(2) << current->discount * 105.0 << "%"<< endl;
        cout << string(40,'-') << endl;
    }
    if(clearScreen) system("pause"); system("cls");
}

void searchProduct(funcListProduct* list) {
    system("cls");
    int choice = 0;
    while(choice != 3){
        cout << VIOLET << "Search Product By" << RESET << endl;
        cout << string(40, '-') << endl;
        cout << "1. Name" << endl;
        cout << "2. ID" << endl;
        cout << "3. Back to main menu" << endl;
        cout << string(40, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:system("cls"); searchByProductName(list, 1); break;
            case 2:system("cls"); searchByProductID(list, 1); break;
            case 3:system("cls"); break;// Exit the function
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }
}

void sortProductsByBrand(funcListProduct* list) {
    cout << YELLOW << "Sorting products by brand..." << RESET << endl;
    if(list->size <= 1) return; // No need to sort if the list is empty or has only one element
    for(funcProductNode* i = list->head; i != NULL; i = i->next) {
        for(funcProductNode* j = i->next; j != NULL; j = j->next) {
            if(i->brand > j->brand) {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->category, j->category);
                swap(i->brand, j->brand);
                swap(i->price, j->price);
                swap(i->unit, j->unit);
                swap(i->stock, j->stock);
                swap(i->discount, j->discount);
            }
        }
    }
}

void sortProductsByCategory(funcListProduct* list) {
    cout << YELLOW << "Sorting products by category..." << RESET << endl;
    if(list->size <= 1) return; // No need to sort if the list is empty or has only one element
    for(funcProductNode* i = list->head; i != NULL; i = i->next) {
        for(funcProductNode* j = i->next; j != NULL; j = j->next) {
            if(i->category > j->category) {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->category, j->category);
                swap(i->brand, j->brand);
                swap(i->price, j->price);
                swap(i->unit, j->unit);
                swap(i->stock, j->stock);
                swap(i->discount, j->discount);
            }
        }
    }
}

void sortProductsByPrice(funcListProduct* list) {
    cout << YELLOW << "Sorting products by price..." << RESET << endl;
    if(list->size <= 1) return; // No need to sort if the list is empty or has only one element
    for(funcProductNode* i = list->head; i != NULL; i = i->next) {
        for(funcProductNode* j = i->next; j != NULL; j = j->next) {
            if(i->price > j->price) {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->category, j->category);
                swap(i->brand, j->brand);
                swap(i->price, j->price);
                swap(i->unit, j->unit);
                swap(i->stock, j->stock);
                swap(i->discount, j->discount);
            }
        }
    }
}

void sortProducts(funcListProduct* list) {
    system("cls");
    int choice = 0;
    while(choice != 4){
        cout << VIOLET << "Sort Products By" << RESET << endl;
        cout << string(40, '-') << endl;
        cout << "1. Brand" << endl;
        cout << "2. Category" << endl;
        cout << "3. Price" << endl;
        cout << "4. Back to main menu" << endl;
        cout << string(40, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:system("cls"); sortProductsByBrand(list); displayAllProducts(list, 1); break;
            case 2:system("cls"); sortProductsByCategory(list); displayAllProducts(list, 1); break;
            case 3:system("cls"); sortProductsByPrice(list); displayAllProducts(list, 1); break;
            case 4:system("cls"); break; // Exit the function
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }
    
}