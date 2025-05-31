#include<iostream>
#include<string>
#include"function/authentication.h"
#include"function/customer.h"
#include"function/admin.h"
#include"function/storage.h"
#include"function/cashier.h"
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
        switch(authenticateUser()){
            case CUSTOMER: customerMenu(); break;
            case CASHIER: cashierMenu(); break;
            case MANAGER: break;
            case ADMIN: adminMenu(); break;
        }
    }
    return 0;
}