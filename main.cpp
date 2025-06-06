#include<iostream>
#include"function/catch_temporary_user.h"
#include"function/authentication.h"
#include"function/admin.h"
#include"function/customer.h"
#include"function/manager.h"
#include"function/color.h"
#include"function/utils.h"
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
            case CUSTOMER:customerMenu();break;
            // case CASHIER:cashierMenu();break;
            // case MANAGER:managerMenu();break;
            case ADMIN:funcAdminMenu();break;  
        }       
    }
}

