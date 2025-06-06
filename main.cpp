#include<iostream>
#include"include/catch_temporary_user.h"
#include"include/authentication.h"
#include"include/admin.h"
#include"include/customer.h"
#include"include/manager.h"
#include"include/color.h"
#include"include/utils.h"
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
            case CUSTOMER:{
                system("cls");
                customerMenu();
                break;}
            // case CASHIER:cashierMenu();break;
            // case MANAGER:managerMenu();break;
            case ADMIN:{
                system("cls");
                adminMenu();
                break;  
            }

        }       
    }
}

