#include "SerialComManager.h"

SerialComManager::SerialComManager(
    TimeManager *timeManager,
    HttpServerManager *httpServerManager)
{
    this->timeManager = timeManager;
    this->httpServerManager = httpServerManager;
    lastSendTime = 0;
    lastReceiveTime = 0;
}

void SerialComManager::receiveSerialData()
{
    static String serialPortData = "";
    char c;
    if (Serial2.available() > 0)
    {
        while (c != '}' && Serial2.available() > 0)
        {
            c = Serial2.read();
            serialPortData += (char)c;
        }
    }
    if (c == '}') // Data frame tail check
    {
        Serial.println(serialPortData);
        httpServerManager->getWebSocket()->textAll(serialPortData);
        serialPortData = "";
    }
}

void SerialComManager::sendSerialData()
{
}
