#include<iostream>
#include"include/auth/authentication.h"
#include"include/admin.h"
#include"include/cashier.h"
#include"include/customer.h"
#include"include/manager.h"
#include"include/color.h"
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
            case ADMIN:funcAdminMenu();break;  
        }       
    }
}

