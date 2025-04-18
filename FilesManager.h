#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class FileManager {
public:
   
    static void saveHighscore( int number);
    static int loadHighscore();
};

#endif // FILE_MANAGER_H

