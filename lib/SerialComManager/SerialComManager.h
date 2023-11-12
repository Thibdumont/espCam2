#ifndef SERIAL_COM_MANAGER_H
#define SERIAL_COM_MANAGER_H

#include <ArduinoJson.h>
#include "TimeManager.h"
#include "HttpServerManager.h"
#include "WifiManager.h"
#include "RobotStateManager.h"
#include "RobotSettingManager.h"

#define SYSTEM_DATA_SEND_INTERVAL 500

class SerialComManager
{
public:
    SerialComManager(TimeManager *, HttpServerManager *, WifiManager *, RobotStateManager *, RobotSettingManager *);
    void receiveSerialData();

private:
    TimeManager *timeManager;
    HttpServerManager *httpServerManager;
    WifiManager *wifiManager;
    RobotStateManager *robotStateManager;
    RobotSettingManager *robotSettingManager;
    boolean syncRequestSent;
    unsigned long lastSendTime;
    unsigned long lastReceiveTime;
    uint16_t radarDistance;
    float unoLoopDuration;
    float espLoopDuration;
    float batteryVoltage;
    int wifiStrength;
    void processCommands(String serialPortData);
    void sendDataToClient();
    void handleUnoSyncRequest();
};

#endif