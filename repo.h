#ifndef REPO_H
#define REPO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <user.h>
#include <fileManager.h>
#include <transaction.h>
#include <account.h>

using namespace std;

class Repo {
    FileManager file;

    vector<User> all_user;

    public:
        Repo() {
            all_user = file.loadAll();
        }
    
        void addUser( User user ) {
        all_user.push_back(user);
            cout << "user: " << user.getEmail() << "is added."<<endl;
        }

        void removeUser(int id) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
            
            if (it != all_user.end()) {
                cout << "User with ID " << id << " removed." << std::endl;
                all_user.erase(it);
                Optionally: file.saveData(all_user);
            } else {
                cout << "User with ID " << id << " not found." << std::endl;
            }
        }

        User findUser( int id ) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
            return it[0]; 
        }
        User findUser( string email ) {
            auto it = find_if(all_user.begin(), all_user.end(),
            [email](User& user) { return user.getEmail() == email; });
            return it[0];
        }   

        void updateUser(int id, const User& updatedUser) {
            auto it = std::find_if(all_user.begin(), all_user.end(),
            [id](User& user) { return user.getID() == id; });
        
            if (it != all_user.end()) {
                *it = updatedUser;
                std::cout << "User with ID " << id << " updated." << std::endl;
                file.saveData(all_user);
            } else {
            std::cout << "User with ID " << id << " not found." << std::endl;
            }
        }

        void save() {
            file.saveData(all_user);
        }
};
#endif