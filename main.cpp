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
    vector<SavingsAccount> all_acc = repo.getAllSavingAcc();

    for(auto &acc : all_acc) {
        cout << "laoded Account: " << acc.getAccountNumber() << endl;
    }

    int uniqueID = chrono::system_clock::now().time_since_epoch().count();
    cout << "uniqueID: " << uniqueID << endl;

    repo.save();
    return 0;
}