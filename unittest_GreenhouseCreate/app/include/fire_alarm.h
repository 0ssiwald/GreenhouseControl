#ifndef FIRE_ALARM_H
#define FIRE_ALARM_H

#include <QObject>

class FireAlarm: public QObject {
    Q_OBJECT
public slots:
    void smokeDetected();
signals:
    void sendAlarm();
};

#endif // FIRE_ALARM_H
