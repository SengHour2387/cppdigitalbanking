#include <iostream>
#include "user.h"
#include "console.h"
#include "bank.h"
using namespace std;

int main() {
    Bank bank = Bank();
    int choice;
    bool loggedIn = false;
    while (!loggedIn) {
        choice = BankConsole::displayMenu();
        if (choice == 1) {
            BankConsole::signUp(bank);
        } else if (choice == 2) {
            loggedIn = BankConsole::logIn(bank);
        } else if (choice == 3) {
            cout << "Exiting program." << endl;
            return 0;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    bool running = true;
    while (running) {
        int userChoice = BankConsole::displayUserMenu();
        switch (userChoice) {
            case 1:
                BankConsole::createAccount(bank);
                break;
            case 2:
                BankConsole::depositMenu(bank);
                break;
            case 3:
                BankConsole::withdrawMenu(bank);
                break;
            case 4:
                bank.viewAccounts();
                break;
            case 5:
                cout << "Logging out..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
    
    // Save and exit
    Repo repo = Repo();
    repo.save();
    return 0;
}