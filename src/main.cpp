#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"
#include "HttpServerManager.h"

TimeManager *timeManager;
WifiManager *wifiManager;
HttpServerManager *httpServerManager;

void setup()
{
  Serial.begin(115200);
  timeManager = new TimeManager();
  wifiManager = new WifiManager();
  httpServerManager = new HttpServerManager();
}

void loop()
{
  timeManager->updateLoopTime();
  // timeManager->displayLoopPerformanceStats();

  // Permet de laisser "respirer" l'esp et au serveur web de traiter les requêtes
  // delay(2);
}
