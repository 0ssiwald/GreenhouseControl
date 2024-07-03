#include <QtTest>
#include "sensors_actors/sensor.h"

class TestFlowSensor : public QObject {
    Q_OBJECT

    FlowSensor* sut;

public:
    explicit TestFlowSensor(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testIsFlowDetected();
};

