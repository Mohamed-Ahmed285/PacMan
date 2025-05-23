#include "FilesManager.h"
#include <fstream>
#include <stdexcept>
using namespace std;

void FileManager::saveHighscore(int number) {
    ofstream file("hs.txt");
    if (!file) {
        throw runtime_error("Failed to open file for writing.");
    }
    file << number;
}

int FileManager::loadHighscore() {
    ifstream file("hs.txt");

    if (!file) {
        throw runtime_error("Failed to open file for writing.");
    }

    int number;
    file >> number;



    file.close();
    return number;
}
