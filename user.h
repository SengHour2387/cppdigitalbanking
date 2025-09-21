#ifndef USER_H
#define USER_H

using namespace std;
#include <transaction.h>
#include <iostream>

class User {
    int id;
    string name; 
    string email;
    string password;
    public:
        User() {};
        User(int id, string name, string email, string password) {
            this->id = id;
            this->name = name;
            this->email = email;
            this->password = password;
        };
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
};

#endif