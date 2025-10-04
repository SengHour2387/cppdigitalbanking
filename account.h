#ifndef    ACCOUNT_H
#define    ACCOUNT_H
using namespace std;
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include "user.h"

using namespace chrono;

class Account {
    protected:
    int accountNumber = 0;
    double balance;
    int type = 1;
    public:

        double getBalance() const {
            return balance;
        }

        int getType() const {
            return type;
        } 

        int getAccountNumber() const {
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

        bool withdraw( User user, double amount) {
            if (balance >= amount)
            {
                balance -= amount;
                return true;
            }
            return false;
            
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
    long long accountCreationDate;  
    long long lastInterestAppliedDate;

    public:
        SavingsAccount():Account() {
            accountCreationDate = std::time(nullptr);
        lastInterestAppliedDate = accountCreationDate;
        };
        SavingsAccount(double balance, int interestRate, int accountNum) : Account(balance, accountNum, 0) {
        accountCreationDate = std::time(nullptr);
        lastInterestAppliedDate = accountCreationDate;
        }
        SavingsAccount(double balance, long long date, long long lastDate, int accountNum) : Account(balance, accountNum, 0) {
        accountCreationDate = std::time(nullptr);
        lastInterestAppliedDate = accountCreationDate;

        }

    long long getAccCreationDate() {
        return accountCreationDate;
    }

    long long getLastAppliedDate() {
        return lastInterestAppliedDate;
    }

    double getAnnualInterestRate() const {
        if (balance <= 25000) return 0.0020;
        else if (balance <= 50000) return 0.0025;
        else if (balance <= 100000) return 0.0035;
        else return 0.0050;
    }

    void applyInterest(double rate) {
        long long now = std::time(nullptr);
        long long diff = now - lastInterestAppliedDate;

        if (diff >= 30 * 24 * 60 * 60) {
            balance += balance * rate;
            lastInterestAppliedDate = now;
            cout << "Interest applied! New balance: " << balance << "\n";
        }
    }

    bool deposit(User user, double amount) {
        applyInterest(getAnnualInterestRate());
        return Account::deposit(user, amount);
    }

    bool withdraw(User user, double amount) {
        applyInterest(getAnnualInterestRate());
        return Account::withdraw(user, amount);
    }   

};


class CheckingAccount : public Account {
    double overdraftLimit;
    public:
        double getOverdraftLimit() const {
            return overdraftLimit;
        }
        CheckingAccount():Account() {};
        CheckingAccount(double balance, double overdraftLimit,int accountNum) 
        : Account(balance, accountNum,1) {
            this->overdraftLimit = overdraftLimit;
        }


        bool withdraw(User user, double amount) {
        vector<int> ids = user.getAllAccount();
        for (int& id : ids) {
            if (id == accountNumber) {
                if (balance + overdraftLimit >= amount) {
                    balance -= amount;
                    cout << "Withdrawn $" << amount << " successfully. New balance: $" << balance << endl;
                    if (balance < 0)
                        cout << "Warning: You are using $" << -balance << " of your overdraft limit." << endl;
                    return true;
                } else {
                    cout << "Withdrawal failed: Exceeds overdraft limit!" << endl;
                    return false;
                }
            }
        }
        cout << user.getEmail() << " doesn't own this account!!" << endl;
        return false;
    }
};

#endif