#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"
#include "HttpServerManager.h"

#define CAMERA_MODEL_M5STACK_WIDE
#define RXD2 33
#define TXD2 4

TimeManager *timeManager;
WifiManager *wifiManager;
HttpServerManager *httpServerManager;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  timeManager = new TimeManager();
  wifiManager = new WifiManager();
  httpServerManager = new HttpServerManager();
}

void loop()
{
  timeManager->updateLoopTime();
  // timeManager->displayLoopPerformanceStats();

  // Permet de laisser "respirer" l'esp et au serveur web de traiter les requêtes
  // delay(1000);
}
