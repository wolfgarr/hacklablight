#ifndef LightStatusHandler_h
#define LightStatusHandler_h

#include "Arduino.h"

class LightStatusHandler
{
  public:
    LightStatusHandler(int minOn, int maxOff);
    bool hasChanged(int reading);

    bool _lightStatus;
  private:
    int _minOn;
    int _maxOff;

    unsigned long _lastChangeMillis;
};

#endif