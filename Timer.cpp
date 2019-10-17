#include "Timer.h"

Timer::Timer() {
    _start = 0;
    reset();
}

void Timer::reset() {
    _lastTime = millis() - _start;
    _start = millis();
}

String Timer::getLastTime() {
    unsigned long totalSeconds = _lastTime / 1000;
    int totalMinutes = totalSeconds / 60;
    int totalHours = totalMinutes / 60;
    int totalDays = totalHours / 24;

    String str = "";
    
    if (totalDays) {
        str += totalDays ;
        str += " days, ";
        str += totalHours % 24 ;
        str +=" hours";
    } else if (totalHours) {
        str += totalHours ;
        str += " hours, ";
        str += totalMinutes % 60 ;
        str +=" minutes";
    } else if (totalMinutes) {
        str += totalMinutes ;
        str += " minutes, ";
        str += totalSeconds % 60 ;
        str +=" seconds";
    } else {
        str += totalSeconds;
        str += " seconds";
    }

    return str;
}