#pragma once

#include <QObject>
#include <QtTest>
#include "sensors_actors/sensor_control.h"
#include "greenhouse/greenhouse.h"
#include "sensors_actors/sensor.h"
#include "greenhouse/plant.h"

class MockPlant: public Plant {
public:
    MockPlant() = default;
    std::string getPlantName() override {return "Test";}
};


class TestSensorControl : public QObject {
    Q_OBJECT

    SensorControl *sut;
    MockPlant* mock_plant1_;
    MockPlant* mock_plant2_;

    Sensor* mock_temperature_sensor_;
    Sensor* mock_humidity_sensor_;
    Greenhouse* mock_greenhouse_;

public:
    explicit TestSensorControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testMeasureTemperature();
    void testMeasureHumidity();
    void testMeasureSoilMoistures();
};
