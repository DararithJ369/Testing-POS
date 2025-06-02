#include<iostream>
#include"function/authentication.h"
#include"function/admin.h"
// #include"function/cashier.h"
#include"function/customer.h"
#include"function/manager.h"
using namespace std;

enum ROLE{
    CUSTOMER = 1,
    CASHIER,
    MANAGER,
    ADMIN
};

int main(){
    while(true){
        switch(login()){
            // case CUSTOMER:customerMenu();break;
            // case CASHIER:cashierMenu();break;
            // case MANAGER:managerMenu();break;
            case ADMIN:adminMenu();break;  
        }       
    }
}

