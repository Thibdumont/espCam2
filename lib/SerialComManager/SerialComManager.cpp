#include "SerialComManager.h"

SerialComManager::SerialComManager(
    TimeManager *timeManager,
    HttpServerManager *httpServerManager,
    WifiManager *wifiManager,
    RobotStateManager *robotStateManager,
    RobotSettingManager *robotSettingManager)
{
    this->timeManager = timeManager;
    this->httpServerManager = httpServerManager;
    this->wifiManager = wifiManager;
    this->robotStateManager = robotStateManager;
    this->robotSettingManager = robotSettingManager;
    lastSendTime = 0;
    lastReceiveTime = 0;
    syncRequestSent = false;
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

        processCommands(serialPortData);
        sendDataToClient();

        // After receiving data from Uno for first time, we ask for a sync request
        handleUnoSyncRequest();
    }
}

void SerialComManager::processCommands(String serialPortData)
{
    StaticJsonDocument<300> json;
    deserializeJson(json, serialPortData);
    serialPortData = "";
    if (json.containsKey("syncRequest"))
    {
        // Serial.println("SyncRequest received");
        serializeJson(robotSettingManager->getJsonDocument(), Serial2);
        // serializeJson(robotSettingManager->getJsonDocument(), Serial);
    }

    // serializeJson(json, Serial);

    robotStateManager->extractJson(json);

    // Handle the switch between SoftAP and Local network mode
    wifiManager->detectWifiModeChange(robotStateManager->wifiSoftApMode);
}

void SerialComManager::sendDataToClient()
{
    StaticJsonDocument<300> json;

    json["heartbeat"] = robotStateManager->heartbeat;
    if (robotStateManager->radarDistance != radarDistance)
    {
        radarDistance = robotStateManager->radarDistance;
        json["radarDistance"] = radarDistance;
    }
    if (robotStateManager->unoLoopDuration != unoLoopDuration)
    {
        unoLoopDuration = robotStateManager->unoLoopDuration;
        json["unoLoopDuration"] = unoLoopDuration;
    }
    if (robotStateManager->batteryVoltage != batteryVoltage)
    {
        batteryVoltage = robotStateManager->batteryVoltage;
        json["batteryVoltage"] = batteryVoltage;
    }
    if (wifiManager->getWifiStrength() != wifiStrength)
    {
        wifiStrength = wifiManager->getWifiStrength();
        json["wifiStrength"] = wifiStrength;
    }
    if (timeManager->getLoopAverageDuration() != espLoopDuration)
    {
        espLoopDuration = timeManager->getLoopAverageDuration();
        json["espLoopDuration"] = espLoopDuration;
    }

    char data[300];
    serializeJson(json, data, 300);

    httpServerManager->getWebSocket()->textAll(data);
}

void SerialComManager::handleUnoSyncRequest()
{
    if (!syncRequestSent)
    {
        // Send init settings to Uno before sync request
        serializeJson(robotSettingManager->getJsonDocument(), Serial2);

        StaticJsonDocument<20> json;
        json["syncRequest"] = true;
        serializeJson(json, Serial2);

        syncRequestSent = true;
    }
}
