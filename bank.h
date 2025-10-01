#ifndef BANK_H
#define BANK_H
#include <iostream>
#include "user.h"
#include <vector>
#include "repo.h"
#include <chrono>
using namespace std;
class Bank {
    Repo repo = Repo();
    public:
    User currentUser = User();

    Bank() {};

        void signUp(User user) {             
            Account usd = CheckingAccount();
            user.addAccount(usd.getAccountNumber());
            repo.addUser(user);
        }

        void deposit( double amount, int accountID ) {
            Account acc = repo.findAccount( accountID );
            acc.deposit( currentUser,amount );
        }

        void addSavingAcc( SavingsAccount account ) {
            repo.addSavingAcc(account);
            currentUser.addAccount(account.getAccountNumber());
            repo.updateUser(currentUser.getID(), currentUser);
        }
        void addCheckingAcc( CheckingAccount account ) {
            repo.addCheckingAcc(account);
            currentUser.addAccount(account.getAccountNumber());
            repo.updateUser(currentUser.getID(), currentUser);
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
        }

        void save() {
            repo.save();
        }

};

#endif