#include <Arduino.h>
#include "TimeManager.h"

TimeManager *timeManager;

void setup()
{
  Serial.begin(115200);
  timeManager = new TimeManager();
}

void loop()
{
  timeManager->updateLoopTime();
  timeManager->displayLoopPerformanceStats();
}
