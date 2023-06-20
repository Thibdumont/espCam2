#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include "WiFi.h"

class WifiManager
{
public:
    WifiManager();

private:
    String ssid;
    String password;
    void connect();
    void softAP();
};

#endif
