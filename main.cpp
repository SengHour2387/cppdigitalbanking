#include <iostream>
#include "user.h"
#include "console.h"
#include "bank.h"
using namespace std;

int main() {
    Bank bank = Bank();

    vector<User> allUser = bank.getAllUser();
    for(auto &user : allUser) {
        cout << "laoded User: " << user.getName() << endl;
    }

    Repo repo = Repo();
    vector<Account> all_acc =   repo.getAllAccounts();

    for(auto &acc : all_acc) {
        cout << "laoded Account: " << acc.getAccountNumber() << endl;
    }

    bank.save();
    return 0;
}