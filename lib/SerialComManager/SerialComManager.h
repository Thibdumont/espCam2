#ifndef SERIAL_COM_MANAGER_H
#define SERIAL_COM_MANAGER_H

#include <ArduinoJson.h>
#include "TimeManager.h"
#include "HttpServerManager.h"
#include "WifiManager.h"

#define SYSTEM_DATA_SEND_INTERVAL 500

class SerialComManager
{
public:
    SerialComManager(TimeManager *, HttpServerManager *, WifiManager *);
    void receiveSerialData();
    void sendSerialData(char *data);

private:
    TimeManager *timeManager;
    HttpServerManager *httpServerManager;
    WifiManager *wifiManager;
    unsigned long lastSendTime;
    unsigned long lastReceiveTime;
};

#endif