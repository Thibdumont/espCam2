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
    syncRequestReceived = false;
    syncReplyReceived = false;
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

        handleUnoSyncRequest();
        serialPortData = "";
    }
}

void SerialComManager::processCommands(String serialPortData)
{
    StaticJsonDocument<400> json;
    deserializeJson(json, serialPortData);

    if (json.containsKey("syncRequest"))
    {
        syncRequestReceived = true;
    }

    if (json.containsKey("syncReply"))
    {
        syncReplyReceived = true;
    }

    robotStateManager->extractRobotStateData(json);

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

    // Process sync reply
    if (syncReplyReceived)
    {
        char data[400];
        serializeJson(robotStateManager->getRobotStateSummary(), data, 400);
        httpServerManager->getWebSocket()->textAll(data);
        syncReplyReceived = false;
    }

    // ESP has started, request a sync to Uno
    if (!syncRequestSent || syncRequestReceived)
    {
        // Send init settings to Uno before sync request
        StaticJsonDocument<512> json = robotSettingManager->getUnoSettingDocument();
        json["syncRequest"] = true;
        serializeJson(json, Serial2);

        syncRequestSent = true;
        syncRequestReceived = false;
    }
}
