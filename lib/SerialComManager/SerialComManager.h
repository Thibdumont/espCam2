#ifndef SERIAL_COM_MANAGER_H
#define SERIAL_COM_MANAGER_H

#include <ArduinoJson.h>
#include "TimeManager.h"
#include "HttpServerManager.h"
#include "WifiManager.h"
#include "RobotStateManager.h"

#define SYSTEM_DATA_SEND_INTERVAL 500

class SerialComManager
{
public:
    SerialComManager(TimeManager *, HttpServerManager *, WifiManager *, RobotStateManager *);
    void receiveSerialData();
    void sendSerialData(char *data);
    void requestUnoHandshake();

private:
    TimeManager *timeManager;
    HttpServerManager *httpServerManager;
    WifiManager *wifiManager;
    RobotStateManager *robotStateManager;
    boolean handshakeDone;
    unsigned long lastSendTime;
    unsigned long lastReceiveTime;
    int maxSpeed;
    uint8_t servoAngle;
    uint16_t radarDistance;
    float unoLoopDuration;
    float espLoopDuration;
    float batteryVoltage;
    int wifiStrength;
    void processCommands();
    void sendDataToClient();
};

#endif