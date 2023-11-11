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
    void setMaxSpeed(uint16_t);
    void setServoSpeed(uint16_t);
    void setSafeStopDistance(uint16_t);
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
    String getWifiLanSSID();
    String getWifiLanPassword();
    String getWifiSoftApSSID();
    String getWifiSoftApPassword();

private:
    void init();
    uint16_t maxSpeed;
    uint16_t servoSpeed;
    uint16_t safeStopDistance;
    int cameraResolution;
    int cameraQuality;
    int cameraContrast;
    int cameraBrightness;
    int cameraSaturation;
    String wifiLanSSID;
    String wifiLanPassword;
    String wifiSoftApSSID;
    String wifiSoftApPassword;
};
#endif
