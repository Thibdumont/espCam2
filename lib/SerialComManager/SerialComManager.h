#ifndef SERIAL_COM_MANAGER_H
#define SERIAL_COM_MANAGER_H

#include <ArduinoJson.h>
#include "TimeManager.h"
#include "HttpServerManager.h"

#define SYSTEM_DATA_SEND_INTERVAL 500

class SerialComManager
{
public:
    SerialComManager(TimeManager *, HttpServerManager *);
    void receiveSerialData();
    void sendSerialData();

private:
    TimeManager *timeManager;
    HttpServerManager *httpServerManager;
    unsigned long lastSendTime;
    unsigned long lastReceiveTime;
};

#endif