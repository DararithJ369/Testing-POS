#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct storNode {
    string id, name, code;
    float price;
    int amount;
    storNode* prev;
    storNode* next;
};

extern storNode* head;
extern storNode* tail;

storNode* head = nullptr;
storNode* tail = nullptr;

void addProduct(string id, string name, string code, float price, int amount) {
    storNode* newNODE = new storNode{ id, name, code, price, amount, nullptr, nullptr };
    if (!head) {
        head = tail = newNODE;
    } else {
        tail->next = newNODE;
        newNODE->prev = tail;
        tail = newNODE;
    }
}

void loadfile() {
    ifstream fin("Database/storage.csv");
    string line;

    // Clear existing list
    while (head != nullptr) {
        storNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;

    while (getline(fin, line)) {
        string No, proid, proname, procode, proprice, proamount;
        stringstream ss(line);

        getline(ss, No, ',');
        getline(ss, proid, ',');
        getline(ss, proname, ',');
        getline(ss, procode, ',');
        getline(ss, proprice, ',');
        getline(ss, proamount, ',');

        if (proid.empty() || proname.empty() || procode.empty() || proprice.empty() || proamount.empty())
            continue;

        addProduct(proid, proname, procode, stof(proprice), stoi(proamount));
    }
    fin.close();
}

void saveToFile() {
    ofstream fout("Database/storage.csv");
    storNode* current = head;
    int i = 1;
    while (current) {
        fout << i << "," << current->id << "," << current->name << "," << current->code << "," << current->price << "," << current->amount << endl;
        current = current->next;
        i++;
    }
    fout.close();
}

void display() {
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }

    cout << "=================== product list ========================" << endl;
    cout << "No.\tID\tName\tcode\tprice\tamount" << endl;

    storNode* current = head;
    int i = 1;
    while (current) {
        cout << i << ".\t" << current->id << "\t" << current->name << "\t" << current->code << "\t"
             << current->price << "\t" << current->amount << endl;
        current = current->next;
        i++;
    }
}

void pop_position(int pos) {
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }
    if (pos < 1) {
        cout << "Invalid position" << endl;
        return;
    }

    storNode* current = head;
    int i = 1;
    while (current && i < pos) {
        current = current->next;
        i++;
    }

    if (!current) {
        cout << "Invalid position" << endl;
        return;
    }

    cout << "Delete " << current->name << " successfully" << endl;

    if (current->prev) current->prev->next = current->next;
    else head = current->next;

    if (current->next) current->next->prev = current->prev;
    else tail = current->prev;

    delete current;

    saveToFile();
}

void sort_alpha() {
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }

    bool swapped;
    do {
        swapped = false;
        storNode* current = head;
        while (current && current->next) {
            if (current->name > current->next->name) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->code, current->next->code);
                swap(current->price, current->next->price);
                swap(current->amount, current->next->amount);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    saveToFile();
    display();
}

void sort_category(){
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }

    bool swapped;
    do {
        swapped = false;
        storNode* current = head;
        while (current && current->next) {
            if (current->code > current->next->code) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->code, current->next->code);
                swap(current->price, current->next->price);
                swap(current->amount, current->next->amount);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    saveToFile();
    display();
}

void sort_price(){
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }

    bool swapped;
    do {
        swapped = false;
        storNode* current = head;
        while (current && current->next) {
            if (current->price > current->next->price) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->code, current->next->code);
                swap(current->price, current->next->price);
                swap(current->amount, current->next->amount);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    saveToFile();
    display();
}

void find_product(string productname){
    if (!head) {
        cout << "The storage is empty" << endl;
        return;
    }

    storNode* current = head;
    bool found = false;
    while (current) {
        if (current->name.find(productname) != string::npos) {
            cout << "Found product: " << current->name << " (ID: " << current->id << ", Code: " << current->code
                 << ", Price: " << current->price << ", Amount: " << current->amount << ")" << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No products found with name containing '" << productname << "'" << endl;
    }
}