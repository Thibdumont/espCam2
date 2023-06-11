#ifndef FILE_SYSTEM_MANAGER_H
#define FILE_SYSTEM_MANAGER_H

#include <LittleFS.h>

#define TEST_FILE "/testFS.txt"

class FileSystemManager
{
public:
    FileSystemManager();
    void test();

private:
    void init();
};

#endif
