#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"
#include "HttpServerManager.h"
#include "SerialComManager.h"
#include "CameraManager.h"
#include "FileSystemManager.h"

#define RXD2 33
#define TXD2 4

TimeManager *timeManager;
WifiManager *wifiManager;
HttpServerManager *httpServerManager;
SerialComManager *serialComManager;
CameraManager *cameraManager;
FileSystemManager *fileSystemManager;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // Nécessaire pour que le WIFI accepte de se connecter quand l'ESP et l'arduino sont connectés ensemble ???

  fileSystemManager = new FileSystemManager();
  timeManager = new TimeManager();
  wifiManager = new WifiManager();
  cameraManager = new CameraManager();
  httpServerManager = new HttpServerManager(fileSystemManager);
  serialComManager = new SerialComManager(timeManager, httpServerManager, wifiManager);
}

void loop()
{
  timeManager->updateLoopTime();
  serialComManager->receiveSerialData();
  // timeManager->displayLoopPerformanceStats();
}
