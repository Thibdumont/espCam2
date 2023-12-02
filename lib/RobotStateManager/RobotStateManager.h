#ifndef ROBOT_STATE_MANAGER_H
#define ROBOT_STATE_MANAGER_H

#include <ArduinoJson.h>
#include "CameraManager.h"
#include "RobotSettingManager.h"
#include "TimeManager.h"

class RobotStateManager
{
public:
    RobotStateManager(CameraManager *, RobotSettingManager *, TimeManager *);
    uint64_t heartbeat;
    // Motor
    uint8_t maxSpeed;
    uint8_t safeStopDistance;
    float turnFactor;
    float autoSpeedFactor;
    uint8_t autoSpeedMode;
    // Radar
    uint16_t radarDistance;
    // Servo
    uint8_t servoAngle;
    uint8_t servoSpeed;
    // Battery
    float batteryVoltage;
    // Wifi
    uint8_t wifiSoftApMode;
    // IR captor
    uint8_t onGround;
    // HUD
    uint8_t hudRadarDistance;
    uint8_t hudBatteryVoltage;
    uint8_t hudOnGround;
    uint8_t hudUnoLoopTime;
    uint8_t hudEspLoopTime;
    //  Debug
    uint32_t unoLoopDuration;

    void extractRobotStateData(StaticJsonDocument<1024> json);
    StaticJsonDocument<1024> getRobotStateSummary();
    StaticJsonDocument<512> getUnoSettingDocument();

    void setMaxSpeed(uint16_t maxSpeed);
    void setServoSpeed(uint16_t servoSpeed);
    void setSafeStopDistance(uint16_t safeStopDistance);
    void setTurnFactor(float turnFactor);
    void setAutoSpeedFactor(float autoSpeedFactor);
    void setAutoSpeedMode(uint8_t autoSpeedMode);
    void setCameraResolution(int cameraResolution);
    void setCameraQuality(int cameraQuality);
    void setCameraContrast(int cameraContrast);
    void setCameraBrightness(int cameraBrightness);
    void setCameraSaturation(int cameraSaturation);
    void setHudRadarDistance(uint8_t hudRadarDistance);
    void setHudBatteryVoltage(uint8_t hudBatteryVoltage);
    void setHudOnGround(uint8_t hudOnGround);
    void setHudUnoLoopTime(uint8_t hudUnoLoopTime);
    void setHudEspLoopTime(uint8_t hudEspLoopTime);

private:
    CameraManager *cameraManager;
    RobotSettingManager *robotSettingManager;
    TimeManager *timeManager;
};

#endif
