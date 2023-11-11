#include "RobotSettingManager.h"

RobotSettingManager::RobotSettingManager()
{
    init();
    loadSettings();
}

void RobotSettingManager::init()
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

    StaticJsonDocument<512> json = this->getJsonDocument();

    // Serialize JSON to settings.json
    if (serializeJson(json, file) == 0)
    {
        Serial.println("Failed to write settings to settings.json");
    }

    file.close();
}

void RobotSettingManager::loadSettings()
{
    StaticJsonDocument<512> json;

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
        maxSpeed = json["maxSpeed"];
        servoSpeed = json["servoSpeed"];
        safeStopDistance = json["safeStopDistance"];
        cameraResolution = json["cameraResolution"];
        cameraQuality = json["cameraQuality"];
        cameraContrast = json["cameraContrast"];
        cameraBrightness = json["cameraBrightness"];
        cameraSaturation = json["cameraSaturation"];
        wifiLanSSID = json["wifiLanSSID"].as<String>();
        wifiLanPassword = json["wifiLanPassword"].as<String>();
        wifiSoftApSSID = json["wifiSoftApSSID"].as<String>();
        wifiSoftApPassword = json["wifiSoftApPassword"].as<String>();

        Serial.println("Loading settings.json ...");
        serializeJsonPretty(json, Serial);
        Serial.println("");
        Serial.println("Settings loaded with success");
    }

    file.close();
}

StaticJsonDocument<512> RobotSettingManager::getJsonDocument()
{
    StaticJsonDocument<512> json;

    json["maxSpeed"] = maxSpeed;
    json["servoSpeed"] = servoSpeed;
    json["safeStopDistance"] = safeStopDistance;
    json["cameraResolution"] = cameraResolution;
    json["cameraQuality"] = cameraQuality;
    json["cameraContrast"] = cameraContrast;
    json["cameraBrightness"] = cameraBrightness;
    json["cameraSaturation"] = cameraSaturation;
    json["wifiLanSSID"] = wifiLanSSID;
    json["wifiLanPassword"] = wifiLanPassword;
    json["wifiSoftApSSID"] = wifiSoftApSSID;
    json["wifiSoftApPassword"] = wifiSoftApPassword;

    return json;
}

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
