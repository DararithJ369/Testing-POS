#pragma once
using namespace std;

struct signupNode{
    string name;
    char gender;
    int age;
    string role;
    string email;
    string password;
    string phone;
    signupNode *next;
};

struct signupStack{
    int size;
    signupNode *top;
};

signupStack* createEmptySignUpStack(){
    signupStack* newlist = new signupStack;
    newlist -> top = NULL;
    newlist -> size = 0;
    return newlist;
}

void push(signupStack* s, string email){
    signupNode* newSignUpNode = new signupNode;
    newSignUpNode -> email = email;
    newSignUpNode -> next = s -> top;
    s -> top = newSignUpNode;
    s -> size++;
}

void display(signupStack* s){
    signupNode* temporary = s -> top;
    while (temporary != NULL){
        cout << temporary -> email << endl;
        temporary = temporary -> next;
    }
}

void readAllUsersFromCSV(signupStack* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) { // Correct way to read each line
            stringstream ss(line);
            string name, ageStr, genderStr, phone, roleStr, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, roleStr, ',');
            getline(ss, email, ',');
            getline(ss, password);
            push(s, email);
        }
        file.close();
    }
}

void writeUserToCSV(string name, int age, char gender, string phone, string role, string email, string password){
    cout << endl << GREEN << "You are sign up successfully!!!" << RESET << endl;
    ofstream file;
    file.open("../Database/users.csv", ios::app);
    if (file.is_open()) {
        file << name << "," << age << "," << gender << "," << phone << "," << role << "," << email << "," << password << endl;
        file.close();
    } else cout << RED << "Unable to open file." << RESET << endl;
}

string getPassword(){
    string password;
    char ch ;
    cout << "Enter password     : " ;
    while((ch = _getch())!= '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";        
            }
        }else{
            password += ch;
            cout << "*";            
        }
    }
    cout << endl;
    return password;
}

string verifyPassword(){
    string password;
    char ch ;
    cout << "Confirm password   : " ;
    while((ch = _getch()) != '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";        
            }
        }else{
            password += ch;
            cout << "*";            
        }
    }
    cout << endl;
    return password;
}

void verifyInfoFromUser(string email, string password) {
    signupNode input;
    bool check = true;
    system("pause");

    // check name
    do {
        system("cls");
        cout << YELLOW << "Verify your information" << RESET << endl;
        if (!check) cout << RED << "Invalid name! Name shouldn't have symbol or number!" << RESET<< endl;
        cout << "Full Name      : "; getline(cin >> ws, input.name);
        check = isAllAlphabets(input.name);
        input.name = Capitalization(input.name);
    } while (!check);

    // check Age
    do {
        system("cls");
        cout << YELLOW << "Verify your information" << RESET << endl;
        if (!check) cout << RED << "Invalid age! Please enter age (1-99)!" << endl;
        cout << "Full Name      : " << input.name << endl;
        cout << "Age            : "; cin >> input.age;
        check = (input.age >= 0 && input.age <= 100);
    } while (!check);

    // check gender
    do {
        system("cls");
        cout << YELLOW << "Verify your information" << RESET << endl;
        if (!check) cout << RED << "Invalid gender! Please enter (M/F)!" << RESET<< endl;
        cout << "Full Name      : " << input.name << endl;
        cout << "Age            : " << input.age << endl;
        cout << "Gender (M/F)   : "; cin >> input.gender;
        input.gender = toupper(input.gender);
        check = (input.gender == 'M' || input.gender == 'F');
    } while (!check);

    // check phone
    do {
        system("cls");
        cout << YELLOW << "Verify your information" << RESET << endl;
        if (!check) cout << RED << "Invalid phone number!"<< RESET << endl;
        cout << "Full Name      : " << input.name << endl;
        cout << "Age            : " << input.age << endl;
        cout << "Gender (M/F)   : " << input.gender << endl;
        cout << "Phone Number   : "; cin >> input.phone;
        check = (isAllDigits(input.phone) && input.phone[0] == '0' && (input.phone.size() == 9 || input.phone.size() == 10));
    } while (!check);

    ofstream user_email;
    user_email.open("../Database/temporary_user.txt", ios::out);
    user_email << email;
    user_email.close();

    writeUserToCSV(input.name, input.age, input.gender, input.phone, "customer", email, password);
    system("pause");
}

bool isEmailExists(signupStack *s, string email){
    signupNode* temporary = s -> top;
    bool check = false;
    while (temporary != NULL){
        if(temporary -> email == email) {
            system("cls");
            cout << RED << "This email has used by other user!" << RESET << endl;
            check = true;  
            break;
        }
        temporary = temporary -> next;
    }
    return check;
    
}

int verifyEmailAndPassFromUser(){
    system("cls");
    signupStack *s = createEmptySignUpStack();
    readAllUsersFromCSV(s, "../Database/users.csv");
    signupNode input;
    int count = 0;
    cout << BOLD << YELLOW << "Create account" << RESET << endl;
    while (true){
        cout << "Enter email        : "; cin >> input.email;
        if (isEmailExists(s, input.email)) continue;
        if (input.email.size() >= 10 && input.email.substr(input.email.size() - 10) == "@gmail.com") break;
        else {
            system("cls");
            cout << RED << "Invalid email" << RESET << endl;
        }
    }
    system("cls");
    cout << GREEN << "Email accepted!" << RESET << endl;
    cout << "Enter email        : " << input.email << endl;

    while (true) {
        input.password = getPassword();
        if (input.password.length() < 6) {
            system("cls");
            cout << RED << "Password must be at least 6 characters!" << RESET << endl;
            cout << "Enter email        : " << input.email << endl;
            continue;
        }
        string confirm = verifyPassword();
        if (confirm == input.password){
            system("cls");
            cout << GREEN << "Account accepted!" << RESET << endl;
            cout << "Enter email        : " << input.email << endl;
            cout << "Enter password     : "; for(int i = 0; i < input.password.length(); ++i){cout << "*";} cout << endl;
            cout << "Confirm password   : "; for(int i = 0; i < input.password.length(); ++i){cout << "*";} cout << "\n" << endl;
            verifyInfoFromUser(input.email, input.password);
            return 1;
        } else{
            system("cls");
            cout << RED << "Confirm password incorrect!" << RESET << endl;
            cout << "Enter email        : " << input.email << endl;
            cout << "Enter password     : ";
            for(int i = 0; i < input.password.length(); ++i){
                cout << "*";
            } cout << endl;
        }
    }
}
