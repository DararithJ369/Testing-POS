#include <iostream> 
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cctype>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "../include/color.h"
#include "../include/utils.h"
#include "../include/catch_temporary_user.h"
#include "../include/manager/user.h"
#include "../include/manager/product.h"
#include "../auth/authentication.h"
#include "../include/admin.h"
#include "../include/customer.h"
#include "../include/manager.h"
using namespace std;

enum ROLE{
    CUSTOMER = 1,
    MANAGER,
    ADMIN
};

int main(){
    while(true){
        switch(login()){
            case CUSTOMER:system("cls"); customerMenu(); break;
            case MANAGER:system("cls"); managerMenu();break;
            case ADMIN:system("cls"); adminMenu(); break;  
        }       
    }
}


