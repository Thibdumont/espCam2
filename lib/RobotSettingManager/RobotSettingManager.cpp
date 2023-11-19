#include "RobotSettingManager.h"

RobotSettingManager::RobotSettingManager()
{
    initFS();
    loadSettings();
}

void RobotSettingManager::initFS()
{
    if (LittleFS.begin())
    {
        Serial.println("FileSystem active");
        Serial.println();
    }
    else
    {
        Serial.println("Unable to activate FileSystem");
    }
}

void RobotSettingManager::saveSettings()
{

    File file = LittleFS.open(SETTINGS_FILE, "w");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    StaticJsonDocument<1024> json = this->getJsonDocument();

    // Serialize JSON to settings.json
    if (serializeJson(json, file) == 0)
    {
        Serial.println("Failed to write settings to settings.json");
    }

    file.close();
}

void RobotSettingManager::loadSettings()
{
    StaticJsonDocument<1024> json;

    File file = LittleFS.open(SETTINGS_FILE, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    DeserializationError error = deserializeJson(json, file);
    if (error)
    {
        Serial.println(F("Failed to read settings.json file"));
    }
    else
    {
        // Motor
        maxSpeed = json["maxSpeed"];
        servoSpeed = json["servoSpeed"];
        safeStopDistance = json["safeStopDistance"];
        turnFactor = json["turnFactor"];
        autoSpeedFactor = json["autoSpeedFactor"];
        autoSpeedMode = json["autoSpeedMode"];
        // Camera
        cameraResolution = json["cameraResolution"];
        cameraQuality = json["cameraQuality"];
        cameraContrast = json["cameraContrast"];
        cameraBrightness = json["cameraBrightness"];
        cameraSaturation = json["cameraSaturation"];
        // Wifi
        wifiLanSSID = json["wifiLanSSID"].as<String>();
        wifiLanPassword = json["wifiLanPassword"].as<String>();
        wifiSoftApSSID = json["wifiSoftApSSID"].as<String>();
        wifiSoftApPassword = json["wifiSoftApPassword"].as<String>();
        // HUD
        hudRadarDistance = json["hudRadarDistance"];
        hudBatteryVoltage = json["hudBatteryVoltage"];
        hudOnGround = json["hudOnGround"];
        hudUnoLoopTime = json["hudUnoLoopTime"];
        hudEspLoopTime = json["hudEspLoopTime"];

        Serial.println("Loading settings.json ...");
        serializeJsonPretty(json, Serial);
        Serial.println("");
        Serial.println("Settings loaded with success");
    }

    file.close();
}

StaticJsonDocument<1024> RobotSettingManager::getJsonDocument()
{
    StaticJsonDocument<1024> json;

    // Motor
    json["maxSpeed"] = maxSpeed;
    json["servoSpeed"] = servoSpeed;
    json["safeStopDistance"] = safeStopDistance;
    json["turnFactor"] = turnFactor;
    json["autoSpeedFactor"] = autoSpeedFactor;
    json["autoSpeedMode"] = autoSpeedMode;
    // Camera
    json["cameraResolution"] = cameraResolution;
    json["cameraQuality"] = cameraQuality;
    json["cameraContrast"] = cameraContrast;
    json["cameraBrightness"] = cameraBrightness;
    json["cameraSaturation"] = cameraSaturation;
    // Wifi
    json["wifiLanSSID"] = wifiLanSSID;
    json["wifiLanPassword"] = wifiLanPassword;
    json["wifiSoftApSSID"] = wifiSoftApSSID;
    json["wifiSoftApPassword"] = wifiSoftApPassword;
    // HUD
    json["hudRadarDistance"] = hudRadarDistance;
    json["hudBatteryVoltage"] = hudBatteryVoltage;
    json["hudOnGround"] = hudOnGround;
    json["hudUnoLoopTime"] = hudUnoLoopTime;
    json["hudEspLoopTime"] = hudEspLoopTime;

    return json;
}

// Motor
void RobotSettingManager::setMaxSpeed(uint16_t maxSpeed)
{
    this->maxSpeed = maxSpeed;
    saveSettings();
}

void RobotSettingManager::setServoSpeed(uint16_t servoSpeed)
{
    this->servoSpeed = servoSpeed;
    saveSettings();
}

void RobotSettingManager::setSafeStopDistance(uint16_t safeStopDistance)
{
    this->safeStopDistance = safeStopDistance;
    saveSettings();
}

void RobotSettingManager::setTurnFactor(float turnFactor)
{
    this->turnFactor = turnFactor;
    saveSettings();
}

void RobotSettingManager::setAutoSpeedFactor(float autoSpeedFactor)
{
    this->autoSpeedFactor = autoSpeedFactor;
    saveSettings();
}

void RobotSettingManager::setAutoSpeedMode(uint8_t autoSpeedMode)
{
    this->autoSpeedMode = autoSpeedMode;
    saveSettings();
}

// Camera
void RobotSettingManager::setCameraResolution(int cameraResolution)
{
    this->cameraResolution = cameraResolution;
    saveSettings();
}
void RobotSettingManager::setCameraQuality(int cameraQuality)
{
    this->cameraQuality = cameraQuality;
    saveSettings();
}
void RobotSettingManager::setCameraContrast(int cameraContrast)
{
    this->cameraContrast = cameraContrast;
    saveSettings();
}
void RobotSettingManager::setCameraBrightness(int cameraBrightness)
{
    this->cameraBrightness = cameraBrightness;
    saveSettings();
}
void RobotSettingManager::setCameraSaturation(int cameraSaturation)
{
    this->cameraSaturation = cameraSaturation;
    saveSettings();
}

int RobotSettingManager::getCameraResolution()
{
    return cameraResolution;
}
int RobotSettingManager::getCameraQuality()
{
    return cameraQuality;
}
int RobotSettingManager::getCameraContrast()
{
    return cameraContrast;
}
int RobotSettingManager::getCameraBrightness()
{
    return cameraBrightness;
}
int RobotSettingManager::getCameraSaturation()
{
    return cameraSaturation;
}

// Wifi
String RobotSettingManager::getWifiLanSSID()
{
    return wifiLanSSID;
}
String RobotSettingManager::getWifiLanPassword()
{
    return wifiLanPassword;
}
String RobotSettingManager::getWifiSoftApSSID()
{
    return wifiSoftApSSID;
}
String RobotSettingManager::getWifiSoftApPassword()
{
    return wifiSoftApPassword;
}

// HUD
void RobotSettingManager::setHudRadarDistance(uint8_t hudRadarDistance)
{
    this->hudRadarDistance = hudRadarDistance;
    saveSettings();
}
void RobotSettingManager::setHudBatteryVoltage(uint8_t hudBatteryVoltage)
{
    this->hudBatteryVoltage = hudBatteryVoltage;
    saveSettings();
}
void RobotSettingManager::setHudOnGround(uint8_t hudOnGround)
{
    this->hudOnGround = hudOnGround;
    saveSettings();
}
void RobotSettingManager::setHudUnoLoopTime(uint8_t hudUnoLoopTime)
{
    this->hudUnoLoopTime = hudUnoLoopTime;
    saveSettings();
}
void RobotSettingManager::setHudEspLoopTime(uint8_t hudEspLoopTime)
{
    this->hudEspLoopTime = hudEspLoopTime;
    saveSettings();
}
