#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <user.h>
#include <transaction.h>
#include <account.h>

using namespace std;

class FileManager {

    fstream streamer;
    
    public:
        FileManager() {
            streamer.open("all_user.bin",ios::binary|ios::trunc);
        }
        void saveData( vector<User> all_user ) {
            size_t size = all_user.size();
            streamer.write(reinterpret_cast<const char*>(&size),sizeof(size));
            for(auto &user : all_user) {
                streamer.write(reinterpret_cast<const char*>(&user),sizeof(User));
            }
        }

        vector<User> loadAll() {
            vector<User> all_user;
            size_t size;
            
            streamer.read(reinterpret_cast<char*>(&size),sizeof(size));

            for( size_t i = 0;i < size;++i ) {
                User user;
                streamer.read( reinterpret_cast<char*>(&user),sizeof(User));
                all_user.push_back(user);
            }

            return all_user;
        }
};
#endif