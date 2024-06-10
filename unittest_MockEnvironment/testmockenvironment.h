#pragma once

#include <QObject>
#include <QtTest>
#include "sensors_actors/sensor_control.h"
#include "sensors_actors/water_control.h"
#include "sensors_actors/mock_environment.h"

class MockPlant: public Plant {
public:
    WaterValve* mock_valve_;
    Sensor* mock_sensor_;
    MockPlant( WaterValve* mock_valve, Sensor* mock_sensor):  mock_valve_(mock_valve), mock_sensor_(mock_sensor) {}
    WaterValve* getWaterValve() override {return mock_valve_;}
    Sensor* getSoilSensor() override {return mock_sensor_;}
};

class TestMockEnvironment : public QObject {
    Q_OBJECT

    MockEnvironment *sut;
    SensorControl* sensor_control_;
    WaterControl* water_control_;

public:
    explicit TestMockEnvironment(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testGetRandomChange();
    void testGenerateNewTemperature();
    void testGenerateNewHumidity();
    void testGenerateNewSoilMoisture();
    void testGenerateNewFlow();
};

