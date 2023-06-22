#include "SerialComManager.h"

SerialComManager::SerialComManager(
    TimeManager *timeManager,
    HttpServerManager *httpServerManager,
    WifiManager *wifiManager)
{
    this->timeManager = timeManager;
    this->httpServerManager = httpServerManager;
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
        Serial.println(serialPortData);
        StaticJsonDocument<200> json;
        deserializeJson(json, serialPortData);

        StaticJsonDocument<200> jsonESP;

        jsonESP["heartbeat"] = json["heartbeat"];
        jsonESP["commandCounter"] = json["commandCounter"];
        jsonESP["maxSpeed"] = json["maxSpeed"];
        jsonESP["servoAngle"] = json["servoAngle"];
        jsonESP["distance"] = json["distance"];
        jsonESP["loopDuration"] = json["loopDuration"];
        jsonESP["batteryVoltage"] = json["batteryVoltage"];
        jsonESP["wifiStrength"] = wifiManager->getWifiStrength();

        char data[200];
        serializeJson(jsonESP, data, 200);

        httpServerManager->getWebSocket()->textAll(data);

        serialPortData = "";
    }
}

void SerialComManager::sendSerialData(char *data)
{
}
