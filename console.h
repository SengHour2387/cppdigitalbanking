#ifndef   CONSOLE_H
#define   CONSOLE_H
#include <iostream>
#include <string>

using namespace std;

class BankConsole {

    public:

    static int displayMenu() {
        cout << "Welcome to the Bank System" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option: ";

        int choice;
        cin >> choice;
        return choice;
    }
};

#endif