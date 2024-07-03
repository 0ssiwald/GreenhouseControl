#include <QtTest>
#include "sensors_actors/mock_environment.h"
#include "clock.h"
#include "log.h"
#include "sensors_actors/sensor_control.h"
#include "notification_control.h"
#include "sensors_actors/water_control.h"
#include "greenhouse/greenhouse_create.h"

class TestGreenhousecontrol : public QObject {
    Q_OBJECT

public:
    explicit TestGreenhousecontrol(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //test the main functionality of the program -> have plants in greenhouse and water them
    void testGreenhousecontrol();
};

