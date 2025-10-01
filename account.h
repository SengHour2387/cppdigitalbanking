#ifndef    ACCOUNT_H
#define    ACCOUNT_H
using namespace std;
#include <iostream>
#include <vector>
#include "user.h"

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

        bool deposit( User user, double amout ) {
            vector<int> ids = user.getAllAccount();
            for( int& id : ids  ) {
                if( id == accountNumber ) {
                    balance += amout;
                    return true;
                }
            }
            cout << user.getEmail() << " doesn't own this account!! "<<endl;
            return false;
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

        bool withdraw( User user, double amount) {
            if( balance > amount ) {
            for( int& id : user.getAllAccount()) {
                    if( id == accountNumber ) {
                    balance -= amount;
                    return true;
                    }
                }
            }
            return false;
        }
};

#endif