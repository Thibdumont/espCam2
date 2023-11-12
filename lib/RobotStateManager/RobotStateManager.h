#ifndef ROBOT_STATE_MANAGER_H
#define ROBOT_STATE_MANAGER_H

#include <ArduinoJson.h>
#include "CameraManager.h"

class RobotStateManager
{
public:
    RobotStateManager(CameraManager *cameraManager);
    uint64_t heartbeat;
    uint8_t maxSpeed;
    uint8_t safeStopDistance;
    uint16_t radarDistance;
    uint8_t servoAngle;
    uint8_t servoSpeed;
    float batteryVoltage;
    uint32_t unoLoopDuration;
    boolean wifiSoftApMode;
    void extractJson(StaticJsonDocument<400> json);
    StaticJsonDocument<400> getRobotStateFirstSyncResponse();

private:
    CameraManager *cameraManager;
};

#endif
