#ifndef    ACOUNT_H
#define    ACOUNT_H
using namespace std;
#include <transaction.h>
#include <iostream>
#include <vector>

enum Currency {
    KHR,
    USD,
};

class Account {
    static int accountNumber;
    double balance;

    Currency currency;

    vector<Transaction> transactions;

    public:
        Account(Currency current) {
            this->balance = 0;
            accountNumber++;
        };
        Account( double balance ,Currency current ) {

            accountNumber++;
            this->balance = balance;
        }
};

class SavingsAccount : public Account {
    double interestRate;
    public:
        SavingsAccount(Currency currency):Account(currency) {};
        SavingsAccount(double balance, double interestRate,Currency currency) : Account( balance,currency) {
            this->interestRate = interestRate;
        }
};


class CheckingAccount : public Account {
    double overdraftLimit;
    public:
        CheckingAccount(Currency currency):Account(currency) {};
        CheckingAccount(double balance, double overdraftLimit,Currency currency) : Account( balance,currency) {
            this->overdraftLimit = overdraftLimit;
        }
};

#endif