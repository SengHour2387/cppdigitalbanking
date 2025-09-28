#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "user.h"
#include "account.h"

using namespace std;

class FileManager {
public:
    FileManager() {}
    void saveAccountCheckingAcc( const vector<CheckingAccount>& all_account ) {
        ofstream file("all_checking_account.bin");
        size_t allSize = all_account.size();
        file.write(reinterpret_cast<const char*>(&allSize), sizeof(allSize));
        for (CheckingAccount account : all_account) {
            size_t accountNumber = account.getAccountNumber();
            size_t balance = account.getBalance();
            size_t type = account.getType();
            size_t overdraftLimit = account.getOverdraftLimit();
            file.write(reinterpret_cast<const char*>(&accountNumber), sizeof(accountNumber));
            file.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
            file.write(reinterpret_cast<const char*>(&overdraftLimit), sizeof(overdraftLimit));
        }

    }
    vector<CheckingAccount> loadAccountCheckingAcc() {
        vector<CheckingAccount> all_account;
        ifstream file("all_checking_account.bin");
        if (file) {
            size_t allSize;
            file.read(reinterpret_cast<char*>(&allSize), sizeof(allSize));
            for (size_t i = 0; i < allSize; ++i) {
                size_t accountNumber;
                size_t balance;
                size_t type;
                size_t overdraftLimit;

                file.read(reinterpret_cast<char*>(&accountNumber), sizeof(accountNumber));
                file.read(reinterpret_cast<char*>(&balance), sizeof(balance));
                file.read(reinterpret_cast<char*>(&type), sizeof(type));
                file.read(reinterpret_cast<char*>(&overdraftLimit), sizeof(overdraftLimit));

                CheckingAccount account(balance,overdraftLimit,accountNumber);
                all_account.push_back(account);
            }
            cout << "Checking Account data loaded successfully." << endl;
        } else {
            cout << "No existing checking account data found." << endl;
        }
        return all_account;
    }    
    void saveAccountSavingAcc( const vector<SavingsAccount>& all_account ) {
        ofstream file("all_saving_account.bin");
        size_t allSize = all_account.size();
        file.write(reinterpret_cast<const char*>(&allSize), sizeof(allSize));
        for (SavingsAccount account : all_account) {
            size_t accountNumber = account.getAccountNumber();
            size_t balance = account.getBalance();
            size_t type = account.getType();
            size_t interestRate = account.getInterestRate();
            file.write(reinterpret_cast<const char*>(&accountNumber), sizeof(accountNumber));
            file.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
            file.write(reinterpret_cast<const char*>(&interestRate), sizeof(interestRate));
        }

    }
    vector<SavingsAccount> loadAccountSavingAcc() {
        vector<SavingsAccount> all_account;
        ifstream file("all_saving_account.bin");
        if (file) {
            size_t allSize;
            file.read(reinterpret_cast<char*>(&allSize), sizeof(allSize));
            for (size_t i = 0; i < allSize; ++i) {
                size_t accountNumber;
                size_t balance;
                size_t type;
                size_t interestRate;
                file.read(reinterpret_cast<char*>(&accountNumber), sizeof(accountNumber));
                file.read(reinterpret_cast<char*>(&balance), sizeof(balance));
                file.read(reinterpret_cast<char*>(&type), sizeof(type));
                file.read(reinterpret_cast<char*>(&interestRate), sizeof(interestRate));

                SavingsAccount account = SavingsAccount(balance,interestRate,accountNumber);
                all_account.push_back(account);
            }
            cout << allSize <<"Saving Account data loaded successfully." << endl;
        } else {
            cout << "No existing saving account data found." << endl;
        }
        return all_account;
    }    
    
    void saveUsers(const vector<User>& all_user) {
        ofstream file("all_user.bin");
        size_t allSize = all_user.size();
        file.write(reinterpret_cast<const char*>(&allSize), sizeof(allSize));
        for (User user : all_user) {
            size_t nameSize = user.getName().size();
            size_t emailSize = user.getEmail().size();
            size_t passwordSize = user.getPassword().size();
            size_t id = user.getID();
            size_t accountCount = user.getAllAccount().size();

            file.write(reinterpret_cast<const char*>(&id), sizeof(id));
            file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
            file.write(user.getName().c_str(), nameSize);
            file.write(reinterpret_cast<const char*>(&emailSize), sizeof(emailSize));
            file.write(user.getEmail().c_str(), emailSize);
            file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
            file.write(user.getPassword().c_str(), passwordSize);
            file.write(reinterpret_cast<const char*>(&accountCount), sizeof(accountCount));
            for (int accountId : user.getAllAccount()) {
                file.write(reinterpret_cast<const char*>(&accountId), sizeof(accountId));
            }

        }
    }

    vector<User> loadUsers() {
        vector<User> all_user;
        ifstream file("all_user.bin");

        if (file) {
            size_t allSize;
            file.read(reinterpret_cast<char*>(&allSize), sizeof(allSize));
            for (size_t i = 0; i < allSize; ++i) {
                size_t id;
                size_t nameSize, emailSize, passwordSize, accountCount;

                file.read(reinterpret_cast<char*>(&id), sizeof(id));
                file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
                string name(nameSize, ' ');
                file.read(&name[0], nameSize);
                file.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
                string email(emailSize, ' ');
                file.read(&email[0], emailSize);
                file.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
                string password(passwordSize, ' ');
                file.read(&password[0], passwordSize);
                file.read(reinterpret_cast<char*>(&accountCount), sizeof(accountCount));

                User user(id, name, email, password);
                for (size_t j = 0; j < accountCount; ++j) {
                    int accountId;
                    file.read(reinterpret_cast<char*>(&accountId), sizeof(accountId));
                    user.addAccount(accountId);
                }
                all_user.push_back(user);
            }
            cout << "Data loaded successfully." << endl;
        } else {
            cout << "No existing data found." << endl;
        }

        return all_user;
    }

};
#endif