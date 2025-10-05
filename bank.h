#ifndef BANK_H
#define BANK_H
#include <iostream>
#include "user.h"
#include <vector>
#include "account.h"
#include "repo.h"
#include <chrono>
using namespace std;

class Bank {
    Repo repo = Repo();
public:
    void withdraw(double amount, int accountID) {
        vector<SavingsAccount> savings = repo.getAllSavingAcc();
        for (auto& acc : savings) {
            if (acc.getAccountNumber() == accountID) {
                 if(acc.withdraw(currentUser, amount)) {
                    SavingsAccount updatedAcc =  acc;
                    repo.updateSavingAccount(updatedAcc);
                    return;
                 } else {
                    cout << "Withdaw from " << accountID << "is failed"<<endl;
                    return;
                 }
            }
        }

        vector<CheckingAccount> checking = repo.getAllCheckingAcc();
        for (auto& acc : checking) {
            if (acc.getAccountNumber() == accountID) {
                if(acc.withdraw(currentUser, amount)) {
                    CheckingAccount updatedAcc = acc;
                repo.updateCheckingAccount(updatedAcc);
                return;
                } else {
                    cout << "Withdaw from " << accountID << "is failed"<<endl;
                }
                
            }
        }
        cout << "Account not found." << endl;
    }
    User currentUser = User();

    void viewAccounts() {
        vector<int> accountIds = currentUser.getAllAccount();
        if (accountIds.empty()) {
            cout << "No accounts found for this user." << endl;
            return;
        }
        cout << "\nAccounts for user: " << currentUser.getName() << endl;
        vector<SavingsAccount> savings = repo.getAllSavingAcc();
        vector<CheckingAccount> checking = repo.getAllCheckingAcc();
        for (int id : accountIds) {
            bool found = false;
            for (const auto& acc : savings) {
                if (acc.getAccountNumber() == id) {
                    cout << "[Savings Account] Account number: " << acc.getAccountNumber()
                         << ", Balance: " <<"$" << acc.getBalance()
                         << ", Interest Rate: " << acc.getAnnualInterestRate() << endl;
                    found = true;
                    break;
                }
            }
            for (const auto& acc : checking) {
                if (acc.getAccountNumber() == id) {
                    cout << "[Checking Account] Account number: " << acc.getAccountNumber()
                         << ", Balance: " << "$" << acc.getBalance()
                         << ", Overdraft Limit: " << acc.getOverdraftLimit() << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Account ID " << id << " not found in system." << endl;
            }
        }
    }

    void transfer(int fromAccountID, int toAccountID, double amount) {

    vector<SavingsAccount> savingsSrc = repo.getAllSavingAcc();
    for (auto& acc : savingsSrc) {
            if (acc.getAccountNumber() == fromAccountID) {
                if (!acc.withdraw(currentUser, amount)) {
                    cout << "Transfer failed: unable to withdraw from source account." << endl;
                    return;
                }
                repo.updateSavingAccount(acc);
                Account target = repo.findAccount(toAccountID);
                if (target.getAccountNumber() == 0) {
                    cout << "Transfer failed: target account not found." << endl;
                    acc.credit(amount);
                    repo.updateSavingAccount(acc);
                    return;
                }
                vector<SavingsAccount> savings = repo.getAllSavingAcc();
                for (auto& t : savings) {
                    if (t.getAccountNumber() == toAccountID) {
                        t.credit(amount);
                        repo.updateSavingAccount(t);
                        cout << "Transfer successful." << endl;
                        return;
                    }
                }
                vector<CheckingAccount> checking = repo.getAllCheckingAcc();
                for (auto& t : checking) {
                    if (t.getAccountNumber() == toAccountID) {
                        t.credit(amount);
                        repo.updateCheckingAccount(t);
                        cout << "Transfer successful." << endl;
                        return;
                    }
                }
                cout << "Transfer failed: unable to credit target account." << endl;
                return;
            }
        }

    vector<CheckingAccount> checkingSrc = repo.getAllCheckingAcc();
    for (auto& acc : checkingSrc) {
            if (acc.getAccountNumber() == fromAccountID) {
                if (!acc.withdraw(currentUser, amount)) {
                    cout << "Transfer failed: unable to withdraw from source account." << endl;
                    return;
                }
                repo.updateCheckingAccount(acc);

                // Credit target
                vector<SavingsAccount> savings = repo.getAllSavingAcc();
                for (auto& t : savings) {
                    if (t.getAccountNumber() == toAccountID) {
                        t.credit(amount);
                        repo.updateSavingAccount(t);
                        cout << "Transfer successful." << endl;
                        return;
                    }
                }
                vector<CheckingAccount> checking = repo.getAllCheckingAcc();
                for (auto& t : checking) {
                    if (t.getAccountNumber() == toAccountID) {
                        t.credit(amount);
                        repo.updateCheckingAccount(t);
                        cout << "Transfer successful." << endl;
                        return;
                    }
                }
                cout << "Transfer failed: target account not found." << endl;
                // refund
                acc.credit(amount);
                repo.updateCheckingAccount(acc);
                return;
            }
        }

        cout << "Source account not found." << endl;
    }

    Bank() {};

        void signUp(User user) {             
            CheckingAccount usd = CheckingAccount(
                0, 10, chrono::system_clock::now().time_since_epoch().count()*(-1)
            );
            user.addAccount(usd.getAccountNumber());
            repo.addUser(user);
            repo.addCheckingAcc(usd);
            repo.save();
        }

        void deposit(double amount, int accountID) {
            vector<SavingsAccount> savings = repo.getAllSavingAcc();
            for (auto& acc : savings) {
                if (acc.getAccountNumber() == accountID) {
                    acc.deposit(currentUser, amount);
                    SavingsAccount updatedAcc = acc;
                    repo.updateSavingAccount(updatedAcc);
                    return;
                }
            }
            vector<CheckingAccount> checking = repo.getAllCheckingAcc();
            for (auto& acc : checking) {
                if (acc.getAccountNumber() == accountID) {
                    acc.deposit(currentUser, amount);
                    CheckingAccount updatedAcc = acc;
                    repo.updateCheckingAccount(updatedAcc);
                    return;
                }
            }
            cout << "Account not found." << endl;
        }

        void addSavingAcc( SavingsAccount account ) {
            currentUser.addAccount(account.getAccountNumber());
            repo.updateUser(currentUser.getID(), currentUser);
            repo.addSavingAcc(account);
        }
        void addCheckingAcc( CheckingAccount account ) {
            currentUser.addAccount(account.getAccountNumber());
            repo.updateUser(currentUser.getID(), currentUser);
            repo.addCheckingAcc(account);
            repo.save();
        }

        bool login(string email, string passsword) {
            User user = repo.findUser( email );
            currentUser = user;
            return user.getPassword() == passsword && user.getEmail() == email;
        }

        vector<User> getAllUser() {
            return repo.getAllUsers();
        }

        void logout() {
            currentUser = User();
            repo.save();
        }

        void save() {
            repo.save();
        }

};

#endif