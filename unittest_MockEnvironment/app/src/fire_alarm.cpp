#include "fire_alarm.h"

void FireAlarm::smokeDetected() {
    emit sendAlarm();
}
