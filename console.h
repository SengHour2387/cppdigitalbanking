#ifndef   CONSOLE_H
#define   CONSOLE_H
#include <iostream>
#include <string>
#include "user.h"
#include "account.h"

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

    static int displayUserMenu() {
        cout << "User Menu" << endl;
        cout << "1. View Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "5. Logout" << endl;
        cout << "Please select an option: ";

        int choice;
        cin >> choice;
        return choice;
    }

    static User getUserInput() {
        string name, email, password;
        int id;

        cout << "Enter your name: ";
        cin >> name;
        cout<< "Enter your id: ";
        cin >> id;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;
        User user = User(id, name, email, password);
        return user;
    }


    static SavingsAccount getSavingAccInput() {
        double balance, interestRate;
        int accountNum;

        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter interest rate (as a decimal, e.g., 0.05 for 5%): ";
        cin >> interestRate;
        cout << "Enter account number: ";
        cin >> accountNum;

        SavingsAccount account = SavingsAccount(balance, interestRate, accountNum);
        return account;
    }
};

#endif