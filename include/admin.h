#pragma once
using namespace std;

void productInventory(funcListProduct* productList){ 
    int choice;
    while(true){
        displayAllProducts(productList, false);
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << BOLD << YELLOW << "Inventory management" << RESET << endl;
        cout << "   1. Add new product\n   2. Modify product\n   3. Short product\n   4. Search product\n   5. Delete product\n   6. Back\n";
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input 
        switch(choice){
            case 1:system("cls"); addNewProduct(productList); break;
            case 2:system("cls"); modifyProduct(productList); break;
            case 3:system("cls"); sortProducts(productList); cout << GREEN << "Product sorted successfully!" << RESET << endl; break;
            case 4:system("cls"); searchProduct(productList); break;
            case 5:system("cls"); deleteProductByID(productList); break;
            case 6:system("cls"); cout << YELLOW << "Returning to the previous menu..." << RESET << endl; system("pause"); system("cls"); return;
            default:system("cls"); cout << RED << "Invalid input! Please try again." << RESET << endl; break;
        }
    }
    
}

void viewUserInformation(funcListUser* userList){
    while(true){
        funcUpdateUserToCSV(userList);
        break;
    }
}

void adminInformation(funcListUser* userList, string loggedEmail){
    int choice;
    while(true){
        system("cls");
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << BOLD << YELLOW << "User management" << RESET << endl;
        cout << "   1. View own information\n   2. View/update user information\n   3. Back\n";
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        cin >> choice; 
        switch(choice){
            case 1:{
                system("cls");
                viewOwnInformation(userList, loggedEmail, 1);
                break;
            }
            case 2:{
                system("cls");
                viewUserInformation(userList);
                break;
            }
            case 3:{
                system("cls");
                cout << YELLOW << "Returning to the previous menu..." << RESET << endl;\
                system("pause");
                system("cls");
                return;
            }
            default:{
                cout << RED << "\nInvalid input! Please try again." << RESET << endl;
                break;
            }
        }
    }
}

void showSignedUpLog() {
    system("cls");
    ifstream log("../Database/userlog.txt");
    if (!log.is_open()) {
        cout << RED << "No log file found." << RESET << endl;
        system("pause");
        return;
    }
    cout << BOLD << YELLOW << "User Log - Signed Up:" << RESET << endl;
    cout << string(50, '-') << endl;
    string line;
    while (getline(log, line)) {
        if (line.find("Signed up") != string::npos)
            cout << line << endl;
    }
    cout << string(50, '-') << endl;
    log.close();
    system("pause");
}

void showSignedInLog() {
    system("cls");
    ifstream log("../Database/userlog.txt");
    if (!log.is_open()) {
        cout << RED << "No log file found." << RESET << endl;
        system("pause");
        return;
    }
    cout << BOLD << YELLOW << "User Log - Signed In:" << RESET << endl;
    cout << string(50, '-') << endl;
    string line;
    while (getline(log, line)) {
        if (line.find("Logged in") != string::npos)
            cout << line << endl;
    }
    cout << string(50, '-') << endl;
    log.close();
    system("pause");
}

void showExitedLog() {
    system("cls");
    ifstream log("../Database/userlog.txt");
    if (!log.is_open()) {
        cout << RED << "No log file found." << RESET << endl;
        system("pause");
        return;
    }
    cout << BOLD << YELLOW << "User Log - Exited:" << RESET << endl;
    cout << string(50, '-') << endl;
    string line;
    while (getline(log, line)) {
        if (line.find("Exited") != string::npos)
            cout << line << endl;
    }
    cout << string(50, '-') << endl;
    log.close();
    system("pause");
}

void showUserLog(){
    int logChoice;
    do {
        system("cls");
        cout << YELLOW << "Check Log In Menu" << RESET << endl;
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "  1. Show Signed Up Log\n";
        cout << "  2. Show Signed In Log\n";
        cout << "  3. Show Exited Log\n";
        cout << "  4. Back\n";
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        cin >> logChoice;
        cin.ignore();
        switch (logChoice) {
            case 1: showSignedUpLog(); break;
            case 2: showSignedInLog(); break;
            case 3: showExitedLog(); break;
            case 4: system("cls"); cout << YELLOW << "Retuning to the previous menu..." << RESET << endl; system("pause"); break;
            default: cout << RED << "Invalid option! Please try again." << RESET << endl; system("pause"); break;
        }
    } while (logChoice != 4);
}

void adminMenu(){
    int choice;
    string loggedEmail = catchEmailFromTemporaryEmail();
    funcListUser* userList = createfuncListUser();
    funcListProduct* productList = createfuncListProduct();    
    funcLoadUsers(userList, "../Database/users.csv");
    loadAllProductsFromCSV(productList, "../Database/products.csv");
    while (true) {
        system("cls");
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Your current role: " << RED << "admin" << RESET << endl;
        cout << "   1. View inventory\n   2. View user information\n   3.   Add new user\n   4. Check log in\n   5. Back\n";
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:system("cls"); productInventory(productList); break;
            case 2:system("cls"); adminInformation(userList, loggedEmail); break;
            case 3:system("cls"); addNewUsers(userList); break;
            case 4:system("cls"); showUserLog(); break;
            case 5:{
                system("cls"); 
                cout << YELLOW << "Returning to previous menu." << RESET << endl;
                string currentEmail = catchEmailFromTemporaryEmail();
                logUserAction(currentEmail, "Exited");
                system("pause");
                return;
            }
            default: cout << RED << "Invalid option! Please try again." << RESET << endl; break;
        }
    }
}