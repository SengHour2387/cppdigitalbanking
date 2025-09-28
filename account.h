#ifndef    ACOUNT_H
#define    ACOUNT_H
using namespace std;
#include <iostream>
#include <vector>

class Account {
    protected:
    int accountNumber = 0;
    double balance;
    int type = 1;

    public:


        double getBalance() {
            return balance;
        }

        int getType() {
            return type;
        } 

        int getAccountNumber() {
            return accountNumber;
        }

        Account() {
            this->balance = 0;
        };
        Account( double balance, int accountNumber, int type) {
            this->type = type;
            this->accountNumber = accountNumber;
            this->balance = balance;
        }
};

class SavingsAccount : public Account {
    double interestRate;
    public:
        double getInterestRate() {
            return interestRate;
        }
        SavingsAccount():Account() {};
        SavingsAccount(double balance, double interestRate,int accountNum) 
        : Account(balance, accountNum,0) {
            this->interestRate = interestRate;
        }
};


class CheckingAccount : public Account {
    double overdraftLimit;
    public:
        double getOverdraftLimit() {
            return overdraftLimit;
        }
        CheckingAccount():Account() {};
        CheckingAccount(double balance, double overdraftLimit,int accountNum) 
        : Account(balance, accountNum,1) {
            this->overdraftLimit = overdraftLimit;
        }
};

#endif