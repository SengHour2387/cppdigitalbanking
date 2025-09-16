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

class SavingsAccount : public Account {
    double interestRate;
    public:
        SavingsAccount() {};
        SavingsAccount(int accountNumber, double balance, double interestRate) : Account(accountNumber, balance) {
            this->interestRate = interestRate;
        }
};


class CheckingAccount : public Account {
    double overdraftLimit;
    public:
        CheckingAccount() {};
        CheckingAccount(int accountNumber, double balance, double overdraftLimit) : Account(accountNumber, balance) {
            this->overdraftLimit = overdraftLimit;
        }
};

#endif