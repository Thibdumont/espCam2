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
    void detectWifiModeChange(boolean softApMode);
    int getWifiStrength();

private:
    RobotSettingManager *robotSettingManager;
    String ssid;
    String password;
    boolean softApMode;
    void startNetworkMode();
    void startSoftApMode();
};

#endif
