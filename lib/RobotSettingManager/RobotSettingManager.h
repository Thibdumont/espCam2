#ifndef ROBOT_SETTING_MANAGER_H
#define ROBOT_SETTING_MANAGER_H

#include <LittleFS.h>
#include <ArduinoJson.h>

#define SETTINGS_FILE "/settings.json"

class RobotSettingManager
{
public:
    RobotSettingManager();
    void saveSettings();
    void loadSettings();
    StaticJsonDocument<512> getJsonDocument();
    StaticJsonDocument<400> getUnoSettingDocument();
    // Motor
    void setMaxSpeed(uint16_t);
    void setServoSpeed(uint16_t);
    void setSafeStopDistance(uint16_t);
    void setTurnFactor(float);
    void setAutoSpeedFactor(float);
    void setAutoSpeedMode(uint8_t);
    // Camera
    void setCameraResolution(int);
    void setCameraQuality(int);
    void setCameraContrast(int);
    void setCameraBrightness(int);
    void setCameraSaturation(int);
    int getCameraResolution();
    int getCameraQuality();
    int getCameraContrast();
    int getCameraBrightness();
    int getCameraSaturation();
    // Wifi
    String getWifiLanSSID();
    String getWifiLanPassword();
    String getWifiSoftApSSID();
    String getWifiSoftApPassword();

private:
    void init();
    // Motor
    uint16_t maxSpeed;
    uint16_t servoSpeed;
    uint16_t safeStopDistance;
    float turnFactor;
    float autoSpeedFactor;
    uint8_t autoSpeedMode;

    // Camera
    int cameraResolution;
    int cameraQuality;
    int cameraContrast;
    int cameraBrightness;
    int cameraSaturation;
    // Wifi
    String wifiLanSSID;
    String wifiLanPassword;
    String wifiSoftApSSID;
    String wifiSoftApPassword;
};
#endif
