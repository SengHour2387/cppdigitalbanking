#ifndef BANK_H
#define BANK_H

#include <user.h>
#include <vector>
#include <repo.h>
using namespace std;
class Bank {

    Repo repo = Repo();
    public:
    User currentUser = User();

    Bank() {
    }

        void signUp() {
            User user = User();
             
            Account usd = CheckingAccount(
                Currency::USD);
            user.addAccount(usd);
            repo.addUser(user);
        }

        bool login(string email, string passsword) {
            User user = repo.findUser( email );
            currentUser = user;
            return user.getPassword() == passsword && user.getEmail() == email;
        }

        void logout() {
            currentUser = User();
        }

        void save() {
            repo.save();
        }

};

#endif