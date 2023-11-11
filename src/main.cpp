#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"
#include "HttpServerManager.h"
#include "SerialComManager.h"
#include "CameraManager.h"
#include "RobotSettingManager.h"
#include "RobotStateManager.h"

#define RXD2 33
#define TXD2 4

TimeManager *timeManager;
WifiManager *wifiManager;
HttpServerManager *httpServerManager;
SerialComManager *serialComManager;
CameraManager *cameraManager;
RobotSettingManager *robotSettingManager;
RobotStateManager *robotStateManager;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // Nécessaire pour que le WIFI accepte de se connecter quand l'ESP et l'arduino sont connectés ensemble ???

  robotSettingManager = new RobotSettingManager();
  timeManager = new TimeManager();
  wifiManager = new WifiManager();
  cameraManager = new CameraManager(robotSettingManager);
  robotStateManager = new RobotStateManager(cameraManager);
  httpServerManager = new HttpServerManager(robotSettingManager, cameraManager, robotStateManager);
  serialComManager = new SerialComManager(timeManager, httpServerManager, wifiManager, robotStateManager, robotSettingManager);
}

void loop()
{
  timeManager->updateLoopTime();
  serialComManager->receiveSerialData();
  // timeManager->displayLoopPerformanceStats();
}
