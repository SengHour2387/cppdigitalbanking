#ifndef REPO_H
#define REPO_H
#include <iostream>
#include <fstream>
#include <vector>
#include "user.h"
#include "fileManager.h"
#include "account.h"
#include <algorithm>


using namespace std;

class Repo {
    FileManager file;
    vector<User> all_user;
    vector<SavingsAccount> all_saving_account;
    vector<CheckingAccount> all_checking_account;

    public:

        Repo() {
            all_user = file.loadUsers();

            for( User& user : all_user ) {
                cout << "User: " << user.getEmail() << " loaded." << endl;
            }

            all_saving_account = file.loadAccountSavingAcc();
            all_checking_account = file.loadAccountCheckingAcc();
        }

        void addSavingAcc( SavingsAccount account ) {
        all_saving_account.push_back(account);
            cout << "account: " << account.getAccountNumber() << " is added."<<endl;
        }

        void addCheckingAcc( CheckingAccount account ) {
        all_checking_account.push_back(account);
            cout << "account: " << account.getAccountNumber() << " is added."<<endl;
        }
    
        void addUser( User user ) {
        all_user.push_back(user);
            cout << "user: " << user.getEmail() << " is added."<<endl;
        }

        void updateCheckingAccount(const CheckingAccount updatedAcc) {
            auto it = find_if( all_checking_account.begin(),all_checking_account.end(),
            [updatedAcc](CheckingAccount& acc) { return acc.getAccountNumber() == updatedAcc.getAccountNumber();});

            if( it != all_checking_account.end()) {
                *it = updatedAcc;
                file.saveAccountCheckingAcc(all_checking_account);
            }
        }
        void updateUser(int id, const User& updatedUser) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
        
            if (it != all_user.end()) {
                *it = updatedUser;
                std::cout << "User with ID " << id << " updated." << std::endl;
                file.saveUsers(all_user);
            } else {
            std::cout << "User with ID " << id << " not found." << std::endl;
            }
        }

        void updateSavingAccount(const SavingsAccount updatedAcc) {
            auto it = find_if( all_saving_account.begin(),all_saving_account.end(),
            [updatedAcc](SavingsAccount& acc) { return acc.getAccountNumber() == updatedAcc.getAccountNumber();});

            if( it != all_saving_account.end()) {
                *it = updatedAcc;
                file.saveAccountSavingAcc(all_saving_account);
            }
        }

        void removeUser(int id) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
            
            if (it != all_user.end()) {
                cout << "User with ID " << id << " removed." << std::endl;
                all_user.erase(it);
                file.saveUsers(all_user);
            } else {
                cout << "User with ID " << id << " not found." << std::endl;
            }
        }

        vector<User> getAllUsers() {
            return all_user;
        }

        vector<SavingsAccount> getAllSavingAcc() {
            return all_saving_account;
        }

        vector<CheckingAccount> getAllCheckingAcc() {
            return all_checking_account;
        }

        User findUser( int id ) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
            return it[0]; 
        }

        Account findAccount( int accountID ) {
            for( SavingsAccount& acc : all_saving_account ) {
                if( acc.getAccountNumber() == accountID ) {
                    return acc;
                }
            }
            for( CheckingAccount& acc : all_checking_account ) {
                if( acc.getAccountNumber() == accountID ) {
                    return acc;
                }
            }
            return Account();
        }

        User findUser( string email ) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [email](User& user) { return user.getEmail() == email; });
            return it[0];
        }   

        

        void save() {
            file.saveAccountSavingAcc(all_saving_account);
            file.saveAccountCheckingAcc(all_checking_account);
            file.saveUsers(all_user);
        }
};
#endif