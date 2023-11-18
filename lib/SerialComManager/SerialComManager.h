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
    void handleUnoSyncRequest();

private:
    TimeManager *timeManager;
    HttpServerManager *httpServerManager;
    WifiManager *wifiManager;
    RobotStateManager *robotStateManager;
    RobotSettingManager *robotSettingManager;
    boolean syncRequestReceived;
    boolean syncReplyReceived;
    boolean syncRequestSent;
    unsigned long lastSendTime;
    unsigned long lastReceiveTime;
    // Radar
    uint16_t radarDistance;
    // IR Captor
    uint8_t onGround;
    // Debug
    float unoLoopDuration;
    float espLoopDuration;
    // Battery
    float batteryVoltage;
    // Wifi
    int wifiStrength;
    void processCommands(String serialPortData);
    void sendDataToClient();
};

#endif