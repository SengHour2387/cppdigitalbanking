#ifndef    TRANSACTION_H
#define    TRANSACTION_H

#include <iostream>
using namespace std;

class Transaction {
    int transactionId;
    double amount;
    string date;
    string fromAccount;
    string toAccount;
    public:
        Transaction() {};
        Transaction(int transactionId, double amount, string date) {
            this->transactionId = transactionId;
            this->amount = amount;
            this->date = date;
        }
};

#endif