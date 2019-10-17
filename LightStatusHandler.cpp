#include "LightStatusHandler.h"

LightStatusHandler::LightStatusHandler(int minOn, int maxOff) {
    _minOn = minOn;
    _maxOff = maxOff;

    _lastChangeMillis = 0;
    _lightStatus = false;
}

bool LightStatusHandler::hasChanged(int reading) {
    bool newStatus;
    if (reading > _minOn) newStatus = true;
    else if (reading < _maxOff) newStatus = false;
    else newStatus = _lightStatus;

    bool hasChanged = newStatus != _lightStatus;
    _lightStatus = newStatus;
    return hasChanged;
}