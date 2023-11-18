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
    float turnFactor;
    float autoSpeedFactor;
    uint8_t autoSpeedMode;
    uint16_t radarDistance;
    uint8_t servoAngle;
    uint8_t servoSpeed;
    float batteryVoltage;
    uint32_t unoLoopDuration;
    uint8_t wifiSoftApMode;
    uint8_t onGround;
    void extractRobotStateData(StaticJsonDocument<400> json);
    StaticJsonDocument<400> getRobotStateSummary();

private:
    CameraManager *cameraManager;
};

#endif
