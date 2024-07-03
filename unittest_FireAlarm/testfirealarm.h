#include <QtTest>
#include "fire_alarm.h"


class TestFireAlarm : public QObject {
    Q_OBJECT

    FireAlarm* sut;

public:
    explicit TestFireAlarm(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testSmokeDetected();
};

