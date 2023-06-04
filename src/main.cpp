#include <Arduino.h>
#include "TimeManager.h"
#include "WifiManager.h"

TimeManager *timeManager;
WifiManager *wifiManager;

void setup()
{
  Serial.begin(115200);
  timeManager = new TimeManager();
  wifiManager = new WifiManager();
}

void loop()
{
  timeManager->updateLoopTime();
  // timeManager->displayLoopPerformanceStats();
}
