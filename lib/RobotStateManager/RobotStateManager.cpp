#include "RobotStateManager.h"

RobotStateManager::RobotStateManager(CameraManager *cameraManager, RobotSettingManager *robotSettingManager)
{
    this->cameraManager = cameraManager;
    this->robotSettingManager = robotSettingManager;
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
    hudRadarDistance = 0;
    hudBatteryVoltage = 0;
    hudOnGround = 0;
    hudUnoLoopTime = 0;
    hudEspLoopTime = 0;

    extractRobotStateData(this->robotSettingManager->getJsonDocument());
}

void RobotStateManager::extractRobotStateData(StaticJsonDocument<1024> json)
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

    // HUD
    if (json.containsKey("hudRadarDistance"))
    {
        hudRadarDistance = (uint8_t)json["hudRadarDistance"];
    }
    if (json.containsKey("hudBatteryVoltage"))
    {
        hudBatteryVoltage = (uint8_t)json["hudBatteryVoltage"];
    }
    if (json.containsKey("hudOnGround"))
    {
        hudOnGround = (uint8_t)json["hudOnGround"];
    }
    if (json.containsKey("hudUnoLoopTime"))
    {
        hudUnoLoopTime = (uint8_t)json["hudUnoLoopTime"];
    }
    if (json.containsKey("hudEspLoopTime"))
    {
        hudEspLoopTime = (uint8_t)json["hudEspLoopTime"];
    }

    // IR captor
    if (json.containsKey("onGround"))
    {
        onGround = (uint8_t)json["onGround"];
    }

    // Debug
    if (json.containsKey("unoLoopDuration"))
    {
        unoLoopDuration = (uint32_t)json["unoLoopDuration"];
    }
}

/**
 * Get robot state summary to be send to the client
 */
StaticJsonDocument<1024> RobotStateManager::getRobotStateSummary()
{
    StaticJsonDocument<1024> json;

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

    // HUD
    json["hudRadarDistance"] = hudRadarDistance;
    json["hudBatteryVoltage"] = hudBatteryVoltage;
    json["hudOnGround"] = hudOnGround;
    json["hudUnoLoopTime"] = hudUnoLoopTime;
    json["hudEspLoopTime"] = hudEspLoopTime;

    return json;
}

StaticJsonDocument<512> RobotStateManager::getUnoSettingDocument()
{
    StaticJsonDocument<512> json;

    json["maxSpeed"] = maxSpeed;
    json["servoSpeed"] = servoSpeed;
    json["safeStopDistance"] = safeStopDistance;
    json["turnFactor"] = turnFactor;
    json["autoSpeedFactor"] = autoSpeedFactor;
    json["autoSpeedMode"] = autoSpeedMode;

    return json;
}

// Motor
void RobotStateManager::setMaxSpeed(uint16_t maxSpeed)
{
    this->maxSpeed = maxSpeed;
    this->robotSettingManager->setMaxSpeed(maxSpeed);
}

void RobotStateManager::setServoSpeed(uint16_t servoSpeed)
{
    this->servoSpeed = servoSpeed;
    this->robotSettingManager->setServoSpeed(servoSpeed);
}

void RobotStateManager::setSafeStopDistance(uint16_t safeStopDistance)
{
    this->safeStopDistance = safeStopDistance;
    this->robotSettingManager->setSafeStopDistance(safeStopDistance);
}

void RobotStateManager::setTurnFactor(float turnFactor)
{
    this->turnFactor = turnFactor;
    this->robotSettingManager->setTurnFactor(turnFactor);
}

void RobotStateManager::setAutoSpeedFactor(float autoSpeedFactor)
{
    this->autoSpeedFactor = autoSpeedFactor;
    this->robotSettingManager->setAutoSpeedFactor(autoSpeedFactor);
}

void RobotStateManager::setAutoSpeedMode(uint8_t autoSpeedMode)
{
    this->autoSpeedMode = autoSpeedMode;
    this->robotSettingManager->setAutoSpeedMode(autoSpeedMode);
}

// Camera
void RobotStateManager::setCameraResolution(int cameraResolution)
{
    this->cameraManager->changeResolution(cameraResolution);
}
void RobotStateManager::setCameraQuality(int cameraQuality)
{
    this->cameraManager->changeQuality(cameraQuality);
}
void RobotStateManager::setCameraContrast(int cameraContrast)
{
    this->cameraManager->changeContrast(cameraContrast);
}
void RobotStateManager::setCameraBrightness(int cameraBrightness)
{
    this->cameraManager->changeBrightness(cameraBrightness);
}
void RobotStateManager::setCameraSaturation(int cameraSaturation)
{
    this->cameraManager->changeSaturation(cameraSaturation);
}

// HUD
void RobotStateManager::setHudRadarDistance(uint8_t hudRadarDistance)
{
    this->hudRadarDistance = hudRadarDistance;
    this->robotSettingManager->setHudRadarDistance(hudRadarDistance);
}
void RobotStateManager::setHudBatteryVoltage(uint8_t hudBatteryVoltage)
{
    this->hudBatteryVoltage = hudBatteryVoltage;
    this->robotSettingManager->setHudBatteryVoltage(hudBatteryVoltage);
}
void RobotStateManager::setHudOnGround(uint8_t hudOnGround)
{
    this->hudOnGround = hudOnGround;
    this->robotSettingManager->setHudOnGround(hudOnGround);
}
void RobotStateManager::setHudUnoLoopTime(uint8_t hudUnoLoopTime)
{
    this->hudUnoLoopTime = hudUnoLoopTime;
    this->robotSettingManager->setHudUnoLoopTime(hudUnoLoopTime);
}
void RobotStateManager::setHudEspLoopTime(uint8_t hudEspLoopTime)
{
    this->hudEspLoopTime = hudEspLoopTime;
    this->robotSettingManager->setHudEspLoopTime(hudEspLoopTime);
}
