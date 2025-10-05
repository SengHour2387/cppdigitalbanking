#ifndef   CONSOLE_H
#define   CONSOLE_H
#include <iostream>
#include <string>
#include <chrono>
#include "user.h"
#include "account.h"
#include "bank.h"

using namespace std;

class BankConsole {
public:

    static int displayMenu() {
        int choice;
        cout << "Welcome to the Bank System" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option: ";
        cin >> choice;
        return choice;
    }

    static int displayUserMenu() {
    cout << "User Menu" << endl;
    cout << "1. Create Account " << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Transfer" << endl;
    cout << "5. View Account" << endl;
    cout << "6. Logout" << endl;
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
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;
        id = chrono::system_clock::now().time_since_epoch().count()*(-1);
        User user = User(id, name, email, password);
        return user;
    }
    static void depositMenu(Bank& bank) {
        int accountID;
        double amount;
        cout << "Enter account number to deposit into: ";
        cin >> accountID;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        bank.deposit(amount, accountID);
        cout << "Deposit complete." << endl;
    }

    static void withdrawMenu(Bank& bank) {
        int accountID;
        double amount;
        cout << "Enter account number to withdraw from: ";
        cin >> accountID;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        bank.withdraw(amount, accountID);
    }

    static void createAccount(Bank& bank) {
        cout << "Create Account" << endl;
        cout << "1. Savings Account" << endl;
        cout << "2. Checking Account" << endl;
        cout << "Select account type: ";
        int type;
        cin >> type;
        if (type == 1) {
            SavingsAccount acc = getSavingAccInput();
            bank.addSavingAcc(acc);
            cout << "Savings account created successfully!" << endl;
        } else if (type == 2) {
            CheckingAccount acc = getCheckingAccInput();
            bank.addCheckingAcc(acc);
            cout << "Checking account created successfully!" << endl;
        } else {
            cout << "Invalid account type." << endl;
        }
    }

    static void transferMenu(Bank& bank) {
        int fromAccountID, toAccountID;
        double amount;
        cout << "Enter your source account number: ";
        cin >> fromAccountID;
        cout << "Enter target account number: ";
        cin >> toAccountID;
        cout << "Enter amount to transfer: ";
        cin >> amount;
        bank.transfer(fromAccountID, toAccountID, amount);
    }

    static void signUp(Bank& bank) {
        string name, email, password;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);
        int id = chrono::system_clock::now().time_since_epoch().count();
        cout << "Your user ID is: " << id << endl;
        User newUser(id, name, email, password);
        bank.signUp(newUser);
        cout << "Sign up successful! You can now log in." << endl;
    }


    static bool logIn(Bank& bank) {
        string email, password;
        cout << "Enter your email: ";
        cin.ignore();
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);
        if (bank.login(email, password)) {
            cout << "Login successful! Welcome, " << bank.currentUser.getName() << "." << endl;
            return true;
        } else {
            cout << "Login failed. Please check your credentials." << endl;
            return false;
        }
    }

    static SavingsAccount getSavingAccInput() {
        double balance, interestRate;
        int accountNum;

        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter interest rate (as a decimal, e.g., 0.05 for 5%): ";
        cin >> interestRate;
        cout << "Please remember your account number: ";
        accountNum = chrono::system_clock::now().time_since_epoch().count()*(-1);
        cout << accountNum << endl;

        SavingsAccount account = SavingsAccount(balance, interestRate, accountNum);
        return account;
    }

    static CheckingAccount getCheckingAccInput() {
        double balance, overDraftLimit;
        int accountNum;

        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter overdraft limit: ";
        cin >> overDraftLimit;
        cout << "Please remember your account number: ";
        accountNum = chrono::system_clock::now().time_since_epoch().count()*(-1);
        cout << accountNum << endl;

        CheckingAccount account = CheckingAccount(balance, overDraftLimit, accountNum);
        return account;
    }

};

#endif