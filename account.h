#ifndef    ACOUNT_H
#define    ACOUNT_H
using namespace std;
#include <transaction.h>
#include <iostream>
#include <vector>

class Account {
    int accountNumber;
    double balance;

    vector<Transaction> transactions;

    public:
        Account() {};
        Account(int accountNumber, double balance) {
            this->accountNumber = accountNumber;
            this->balance = balance;
        }
};

#endif