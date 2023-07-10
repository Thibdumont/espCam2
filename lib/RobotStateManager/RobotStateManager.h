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
    uint16_t radarDistance;
    uint8_t servoAngle;
    float batteryVoltage;
    uint32_t unoLoopDuration;
    boolean wifiSoftApMode;
    void extractJson(StaticJsonDocument<300> json);
    StaticJsonDocument<300> getRobotStateSummary();

private:
    CameraManager *cameraManager;
};

#endif
