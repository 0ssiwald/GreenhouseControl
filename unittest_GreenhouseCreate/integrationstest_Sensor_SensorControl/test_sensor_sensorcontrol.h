#include <QtTest>
#include "sensors_actors/sensor.h"
#include "sensors_actors/sensor_control.h"

class TestSensorSenorControl : public QObject {
    Q_OBJECT
    TemperatureSensor* temperatureSensor;
    HumiditySensor* humiditySensor;
    SoilMoistureSensor* soilSensor1;
    SoilMoistureSensor* soilSensor2;
    SensorControl* sensorControl;
    //Greenhouse gets still mocked only sensors and sensorcontrol are tested
    Greenhouse *mock_greenhouse;

public:
    explicit TestSensorSenorControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void TestMeasureTemperature();
    void TestMeasureHumidity();
    void TestMeasureSoilMoistures();
};

