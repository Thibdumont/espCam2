#include "WifiManager.h"
#include <string.h>

WifiManager::WifiManager()
{
    softApMode = false;
    startNetworkMode();
}

void WifiManager::startNetworkMode()
{
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);

    ssid = "SFR_3228";
    password = "***REMOVED***";

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.print("Local address : ");
    Serial.println(WiFi.localIP());
}

void WifiManager::startSoftApMode()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);

    ssid = "ESP32 AP";
    password = "esp-password";

    WiFi.softAP(ssid, password);

    Serial.print("AP IP address : ");
    Serial.println(WiFi.softAPIP());
}

int WifiManager::getWifiStrength()
{
    if (softApMode)
    {
        return -100;
    }
    else
    {
        return WiFi.RSSI();
    }
}

void WifiManager::detectWifiModeChange(boolean softApMode)
{
    // If the mode changed
    if (softApMode != this->softApMode)
    {
        this->softApMode = softApMode;
        if (softApMode)
        {
            startSoftApMode();
        }
        else
        {
            startNetworkMode();
        }
    }
}
