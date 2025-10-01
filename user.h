#ifndef USER_H
#define USER_H

using namespace std;
#include <vector>
#include <iostream>

class User {
    int id;
    string name;
    string email;
    string password;

    vector<int> allAccount;
    
    public:

        void setName(string name) {
            this->name = name;
        }
        void setEmail(string email) {
            this->email = email;
        }
        void setPassword(string password) {
            this->password = password;
        }

        User() {};
        User(int id, string name, string email, string password) {
            this->id = id;
            this->name = name;
            this->email = email;
            this->password = password;
        };

        vector<int> getAllAccount() {
            return allAccount;
        }

        string getName() {
            return name;
        }
        string getEmail() {
            return email;
        }
        string getPassword() {
            return password;
        }
        int getID() {
            return id;
        }

        void addAccount( int accountID) {
            allAccount.push_back(accountID);
        }
};

#endif