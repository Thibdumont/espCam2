#include "WifiManager.h"

WifiManager::WifiManager(RobotSettingManager *robotSettingManager)
{
    this->robotSettingManager = robotSettingManager;
    softApMode = false;
    startNetworkMode();
}

void WifiManager::startNetworkMode()
{
    WiFi.softAPdisconnect(false);
    WiFi.mode(WIFI_STA);

    ssid = robotSettingManager->getWifiLanSSID();
    password = robotSettingManager->getWifiLanPassword();

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
    WiFi.disconnect(false);
    WiFi.mode(WIFI_AP);

    ssid = robotSettingManager->getWifiSoftApSSID();
    password = robotSettingManager->getWifiSoftApPassword();

    WiFi.softAP(ssid, password);

    Serial.print("AP IP address : ");
    Serial.println(WiFi.softAPIP());
}

int WifiManager::getWifiStrength()
{
    if (softApMode)
    {
        // Can't figure out how to get RSSI in softApMode
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
