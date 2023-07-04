#include "SerialComManager.h"

SerialComManager::SerialComManager(
    TimeManager *timeManager,
    HttpServerManager *httpServerManager,
    WifiManager *wifiManager)
{
    this->timeManager = timeManager;
    this->httpServerManager = httpServerManager;
    this->wifiManager = wifiManager;
    lastSendTime = 0;
    lastReceiveTime = 0;
}

void SerialComManager::receiveSerialData()
{
    static String serialPortData = "";
    char c;
    if (Serial2.available() > 0)
    {
        while (c != '}' && Serial2.available() > 0)
        {
            c = Serial2.read();
            serialPortData += (char)c;
        }
    }
    if (c == '}') // Data frame tail check
    {
        // Serial.println(serialPortData);
        StaticJsonDocument<200> json;
        deserializeJson(json, serialPortData);

        StaticJsonDocument<200> jsonESP;

        jsonESP["heartbeat"] = json["heartbeat"];
        jsonESP["maxSpeed"] = json["maxSpeed"];
        jsonESP["servoAngle"] = json["servoAngle"];
        jsonESP["distance"] = json["distance"];
        jsonESP["unoLoopDuration"] = json["unoLoopDuration"];
        jsonESP["batteryVoltage"] = json["batteryVoltage"];
        jsonESP["wifiStrength"] = wifiManager->getWifiStrength();
        jsonESP["espLoopDuration"] = timeManager->getLoopAverageDuration();

        char data[200];
        serializeJson(jsonESP, data, 200);

        httpServerManager->getWebSocket()->textAll(data);

        serialPortData = "";

        if (json.containsKey("wifiSoftApMode"))
        {
            boolean wifiSoftApMode = json["wifiSoftApMode"].as<String>().equals("true");
            // Handle the switch between SoftAP and Local network mode
            wifiManager->detectWifiModeChange(wifiSoftApMode);
        }
    }
}

void SerialComManager::sendSerialData(char *data)
{
}
