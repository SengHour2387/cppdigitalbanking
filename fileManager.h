#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <user.h>


using namespace std;

class FileManager {

    fstream streamer;

    public:

        FileManager() {
            streamer.open("data.bin",ios::binary|ios::app);
        }
        void saveData(  ) {
            
        }
};
#endif