#include "RobotStateManager.h"

RobotStateManager::RobotStateManager(
    CameraManager *cameraManager)
{
    this->cameraManager = cameraManager;
    maxSpeed = 0;
    safeStopDistance = 0;
    radarDistance = 0;
    servoAngle = 0;
    servoSpeed = 0;
    batteryVoltage = 0;
    unoLoopDuration = 0;
    wifiSoftApMode = false;
}

void RobotStateManager::extractJson(StaticJsonDocument<400> json)
{
    if (json.containsKey("heartbeat"))
    {
        heartbeat = (uint64_t)json["heartbeat"];
    }
    if (json.containsKey("maxSpeed"))
    {
        maxSpeed = (uint8_t)json["maxSpeed"];
    }
    if (json.containsKey("safeStopDistance"))
    {
        safeStopDistance = (uint8_t)json["safeStopDistance"];
    }
    if (json.containsKey("servoAngle"))
    {
        servoAngle = (uint8_t)json["servoAngle"];
    }
    if (json.containsKey("servoSpeed"))
    {
        servoSpeed = (uint8_t)json["servoSpeed"];
    }
    if (json.containsKey("radarDistance"))
    {
        radarDistance = (uint16_t)json["radarDistance"];
    }
    if (json.containsKey("unoLoopDuration"))
    {
        unoLoopDuration = (uint32_t)json["unoLoopDuration"];
    }
    if (json.containsKey("batteryVoltage"))
    {
        batteryVoltage = (float)json["batteryVoltage"];
    }
    if (json.containsKey("wifiSoftApMode"))
    {
        wifiSoftApMode = json["wifiSoftApMode"].as<String>().equals("true");
    }
}

StaticJsonDocument<400> RobotStateManager::getRobotStateFirstSyncResponse()
{
    StaticJsonDocument<400> json;

    json["syncRequest"] = 1;
    json["maxSpeed"] = maxSpeed;
    json["servoAngle"] = servoAngle;
    json["servoSpeed"] = servoSpeed;
    json["radarDistance"] = radarDistance;
    json["safeStopDistance"] = safeStopDistance;
    json["unoLoopDuration"] = unoLoopDuration;
    json["cameraQuality"] = cameraManager->getQuality();
    json["cameraResolution"] = cameraManager->getResolution();
    json["cameraContrast"] = cameraManager->getContrast();
    json["cameraBrightness"] = cameraManager->getBrightness();
    json["cameraSaturation"] = cameraManager->getSaturation();

    return json;
}