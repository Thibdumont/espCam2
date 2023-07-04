#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include "WiFi.h"

class WifiManager
{
public:
    WifiManager();
    void detectWifiModeChange(boolean softApMode);
    int getWifiStrength();

private:
    String ssid;
    String password;
    boolean softApMode;
    void startNetworkMode();
    void startSoftApMode();
};

#endif
