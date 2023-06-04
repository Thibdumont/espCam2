#include "WifiManager.h"

WifiManager::WifiManager()
{
    ssid = "Bernard's WiFi Network";
    // ssid = "SFR_3228";
    password = "***REMOVED***";

    connect();
}

void WifiManager::connect()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("Local address : ");
    Serial.println(WiFi.localIP());
}
