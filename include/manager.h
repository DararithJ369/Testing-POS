#pragma once
using namespace std;

void viewInventory(funcListProduct* productList){ 
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

void information(funcListUser* userlist, string loggedEmail) {
    while(true){        
        system("cls");
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << BOLD << YELLOW << "User management" << RESET << endl;
        cout << "   1. View your information\n   2. View customer information\n   3. Back" << endl;
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: "; 
        int choice;
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1:system("cls"); viewOwnInformation(userlist, loggedEmail, 0); break;
            case 2:system("cls"); funcDisplayUsers(userlist, 1); break;
            case 3:system("cls"); cout << YELLOW << "Returning to the previous menu..." << RESET << endl; system("pause");  return;
            default :system("cls"); cout << RED << "Invalid input! Please try again." << RESET << endl; break; 
        }
    }
}

void posBalance(){
    while(true){
        system("cls");
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << YELLOW << "POS Balance" << RESET << endl;
        cout << "   1. View transaction History\n   2. View Sales Report\n   3. View Balance\n   4. Back" << endl;
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your choice: "; 
        int choice;
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: {
                system("cls");
                ifstream transaction;
                transaction.open("../Database/transactions.csv");
                if(!transaction.is_open()) cout << RED << "File not Found!!" << RESET << endl;
                string line;
                cout << YELLOW << "Transaction History" << RESET << endl;
                cout << string(50, '-') << endl;
                while (getline(transaction, line)) {
                    if (line.empty()) continue; 
                    if (line[0] == '"') line = line.substr(1, line.size() - 2); // Remove quotes if present
                    getline(transaction, line); // Skip header line
                    stringstream ss(line);
                    string datetime, total, products;
                    getline(ss, datetime, ',');
                    getline(ss, total, ',');
                    getline(ss, products);
                    cout << YELLOW << "Date & Time: " << RESET << datetime << endl;
                    cout << YELLOW << "Total: $" << RESET << total << endl;
                    cout << YELLOW << "Products: " << RESET << endl;
                    stringstream prodss(products);
                    string prod;
                    while (getline(prodss, prod, '|')) {
                        stringstream prodinfo(prod);
                        string id, name, qty;
                        getline(prodinfo, id, ':');
                        getline(prodinfo, name, ':');
                        getline(prodinfo, qty, ':');
                        cout << "  - ID: " << id << ", Name: " << name << ", Quantity: " << qty << endl;
                    }
                    cout << string(50, '-') << endl;
                }
                transaction.close();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                ifstream transaction("../Database/transactions.csv");
                if (!transaction.is_open()) {
                    cout << RED << "Transaction file not found!" << RESET << endl;
                    system("pause");
                    break;
                }
                string line;
                double totalSales = 0.0;
                int transactionCount = 0;

                getline(transaction, line); // Skip header line
                while (getline(transaction, line)) {
                    if (line.empty()) continue;
                    stringstream ss(line);
                    string datetime, total, products, user;
                    getline(ss, datetime, ',');
                    getline(ss, total, ',');
                    // skip products and user for summary
                    totalSales += stod(total);
                    transactionCount++;
                }
                transaction.close();

                cout << YELLOW << "Sales Report" << RESET << endl;
                cout << string(50, '-') << endl;
                cout << "Total Transactions: " << transactionCount << endl;
                cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
                cout << string(50, '-') << endl;
                system("pause");
                break;
            }
            case 3:{
                system("cls");
                ifstream balanceFile("Database/total_money.txt");
                if (!balanceFile.is_open()) {
                    cout << RED << "Balance file not found!" << RESET << endl;
                    return;
                }
                string line;
                cout << YELLOW << "POS Balance" << RESET << endl;
                cout << string(50, '-') << endl;
                getline(balanceFile, line); // Read the first line
                if (line.empty()) {
                    cout << RED << "No balance recorded yet." << RESET << endl;
                } else {
                    cout << YELLOW << "Total Balance: $" << line << endl;
                }
                system("pause");
                break;
            }
            case 4:system("cls"); cout << YELLOW << "Returning to the previous menu..." << RESET << endl; system("pause"); return;
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl; break;
        }
    }
}

void managerMenu(){
    string loggedEmail = catchEmailFromTemporaryEmail();
    funcListProduct* productList = createfuncListProduct();
    funcListUser* userList = createfuncListUser();
    loadAllProductsFromCSV(productList, "../Database/products.csv");
    funcLoadUsers(userList, "../Database/users.csv");
    int choice;
    while(true){
        system("cls");
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Your current role: " << CYAN << "manager" << RESET << endl;
        cout << "   1. View inventory\n   2. View user information\n   3. POS Balance\n   4. Back" << endl;
        cout << BOLD << string(50, '-') << RESET << endl;
        cout << "Enter your option: "; cin >> choice;
        cin.ignore(); // Clear input buffer
        switch(choice){
            case 1:system("cls"); viewInventory(productList); break;
            case 2:system("cls"); information(userList, loggedEmail); break;
            case 3:system("cls"); posBalance(); break;
            case 4:{
                system("cls"); 
                cout << YELLOW << "Returning to previous menu." << RESET << endl;
                string currentEmail = catchEmailFromTemporaryEmail();
                logUserAction(currentEmail, "Exited");
                system("pause");
                return;
            }
            default:system("cls"); cout << RED << "Invalid choice! Please try again." << RESET << endl; break;
        }
    }
}