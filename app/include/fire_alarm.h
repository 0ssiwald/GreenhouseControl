#ifndef FIRE_ALARM_H
#define FIRE_ALARM_H

#include <QObject>
#include <string>
#include "sensors_actors/sensor.h"


/*
class SmokeDetector: public Sensor {
    float smoke_threshold_ = 1.0;
    SmokeDetector(float initial_value = 0.0)
        : Sensor(initial_value) {}

    bool isSmokeDetected();
};

class SendWarning {
public:
    virtual bool sendEmail(const std::string&) = 0;
};

//implementation needed

class Warning {
    std::string warning_text_;
    SendWarning* send_warning_;
public:
    bool sendWarning();
};
*/

class FireAlarm: public QObject {
    Q_OBJECT
public slots:
    void smokeDetected();
signals:
    void sendAlarm();
};

#endif // FIRE_ALARM_H
