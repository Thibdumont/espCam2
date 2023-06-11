#include "FileSystemManager.h"

FileSystemManager::FileSystemManager()
{
    init();
}

void FileSystemManager::init()
{
    if (LittleFS.begin())
    {
        Serial.println("FileSystem active");
        Serial.println();
    }
    else
    {
        Serial.println("Unable to activate FileSystem");
    }
    test();
}

void FileSystemManager::test()
{
    File file = LittleFS.open(TEST_FILE);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("File Content:");
    while (file.available())
    {
        Serial.write(file.read());
    }
    Serial.println("File reading done");

    file.close();
}