#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <string.h>
#include "WiFi.h"
#include "RobotSettingManager.h"

class WifiManager
{
public:
    WifiManager(RobotSettingManager *);
    void detectWifiModeChange(uint8_t softApMode);
    int getWifiStrength();

private:
    RobotSettingManager *robotSettingManager;
    String ssid;
    String password;
    uint8_t softApMode;
    void startNetworkMode();
    void startSoftApMode();
};

#endif
