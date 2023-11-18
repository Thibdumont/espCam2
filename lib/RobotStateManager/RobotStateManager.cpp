#include "RobotStateManager.h"

RobotStateManager::RobotStateManager(
    CameraManager *cameraManager)
{
    this->cameraManager = cameraManager;
    maxSpeed = 0;
    safeStopDistance = 0;
    turnFactor = 0;
    autoSpeedFactor = 0;
    autoSpeedMode = 0;
    radarDistance = 0;
    servoAngle = 0;
    servoSpeed = 0;
    batteryVoltage = 0;
    unoLoopDuration = 0;
    wifiSoftApMode = 0;
    onGround = 0;
}

void RobotStateManager::extractRobotStateData(StaticJsonDocument<400> json)
{
    if (json.containsKey("heartbeat"))
    {
        heartbeat = (uint64_t)json["heartbeat"];
    }

    // Motor
    if (json.containsKey("maxSpeed"))
    {
        maxSpeed = (uint8_t)json["maxSpeed"];
    }
    if (json.containsKey("safeStopDistance"))
    {
        safeStopDistance = (uint8_t)json["safeStopDistance"];
    }
    if (json.containsKey("turnFactor"))
    {
        turnFactor = (float)json["turnFactor"];
    }
    if (json.containsKey("autoSpeedFactor"))
    {
        autoSpeedFactor = (float)json["autoSpeedFactor"];
    }
    if (json.containsKey("autoSpeedMode"))
    {
        autoSpeedMode = (uint8_t)json["autoSpeedMode"];
    }

    // Servo
    if (json.containsKey("servoAngle"))
    {
        servoAngle = (uint8_t)json["servoAngle"];
    }
    if (json.containsKey("servoSpeed"))
    {
        servoSpeed = (uint8_t)json["servoSpeed"];
    }

    // Radar
    if (json.containsKey("radarDistance"))
    {
        radarDistance = (uint16_t)json["radarDistance"];
    }

    // Debug
    if (json.containsKey("unoLoopDuration"))
    {
        unoLoopDuration = (uint32_t)json["unoLoopDuration"];
    }

    // Battery
    if (json.containsKey("batteryVoltage"))
    {
        batteryVoltage = (float)json["batteryVoltage"];
    }

    // Wifi
    if (json.containsKey("wifiSoftApMode"))
    {
        wifiSoftApMode = (uint8_t)json["wifiSoftApMode"];
    }

    // IR captor
    if (json.containsKey("onGround"))
    {
        onGround = (uint8_t)json["onGround"];
    }
}

StaticJsonDocument<400> RobotStateManager::getRobotStateSummary()
{
    StaticJsonDocument<400> json;

    json["syncRequest"] = 1;

    // Motor
    json["maxSpeed"] = maxSpeed;
    json["safeStopDistance"] = safeStopDistance;
    json["turnFactor"] = turnFactor;
    json["autoSpeedFactor"] = autoSpeedFactor;
    json["autoSpeedMode"] = autoSpeedMode;

    // Servo
    json["servoAngle"] = servoAngle;
    json["servoSpeed"] = servoSpeed;

    // Radar
    json["radarDistance"] = radarDistance;

    // Debug
    json["unoLoopDuration"] = unoLoopDuration;

    // Camera
    json["cameraQuality"] = cameraManager->getQuality();
    json["cameraResolution"] = cameraManager->getResolution();
    json["cameraContrast"] = cameraManager->getContrast();
    json["cameraBrightness"] = cameraManager->getBrightness();
    json["cameraSaturation"] = cameraManager->getSaturation();

    return json;
}