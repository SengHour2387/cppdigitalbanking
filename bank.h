#ifndef BANK_H
#define BANK_H
#include <iostream>
#include "user.h"
#include <vector>
#include "repo.h"
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

        void deposit() {
            
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