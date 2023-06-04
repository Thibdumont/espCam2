#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"
#include "HttpServerManager.h"
#include "SerialComManager.h"

#define RXD2 33
#define TXD2 4

TimeManager *timeManager;
WifiManager *wifiManager;
HttpServerManager *httpServerManager;
SerialComManager *serialComManager;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  timeManager = new TimeManager();
  wifiManager = new WifiManager();
  httpServerManager = new HttpServerManager();
  serialComManager = new SerialComManager(timeManager, httpServerManager);
}

void loop()
{
  timeManager->updateLoopTime();
  serialComManager->receiveSerialData();
  // timeManager->displayLoopPerformanceStats();

  // Permet de laisser "respirer" l'esp et au serveur web de traiter les requêtes
  // delay(1000);
}
