#include "WifiManager.h"

WifiManager::WifiManager()
{
    connect();
    // softAP();
}

void WifiManager::connect()
{
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

void WifiManager::softAP()
{
    ssid = "ESP32 AP";
    password = "esp-password";

    WiFi.softAP(ssid, password);

    Serial.print("AP IP address : ");
    Serial.println(WiFi.softAPIP());
}
