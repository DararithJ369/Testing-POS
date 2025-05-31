#include <iostream>
#include <ctime>
#include <fstream>
#include "file.h"
// #include <mer.h>

using namespace std;
int main()
{
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
    return 0;
}