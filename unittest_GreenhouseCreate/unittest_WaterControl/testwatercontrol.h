#pragma once

#include <QObject>
#include <QtTest>
#include "sensors_actors/water_control.h"
#include "greenhouse/greenhouse.h"
#include "sensors_actors/water_valve.h"
#include "greenhouse/plant.h"

class MockPlantProfile: public PlantProfile {
public:
    MockPlantProfile() = default;
    int mock_lower_threshold_;
    int mock_upper_threshold_;
    int getLowerWateringThreshold() override {return mock_lower_threshold_;}
    int getUpperWateringThreshold() override {return mock_upper_threshold_;}
};

class MockPlant: public Plant {
public:
    MockPlantProfile* mock_profile_;
    WaterValve* mock_valve_;
    Sensor* mock_sensor_;
    MockPlant(MockPlantProfile* mock_profile, WaterValve* mock_valve, Sensor* mock_sensor) : mock_profile_(mock_profile), mock_valve_(mock_valve), mock_sensor_(mock_sensor) {}
    std::string getPlantName() override {return "Test";}
    MockPlantProfile* getPlantProfile() override {return mock_profile_;}
    WaterValve* getWaterValve() override {return mock_valve_;}
    Sensor* getSoilSensor() override {return mock_sensor_;}
};

class TestWaterControl : public QObject {
    Q_OBJECT

    WaterControl *sut;
    WaterValve* mock_valve_;
    FlowSensor* mock_sensor_;
    Greenhouse* mock_greenhouse_;

    MockPlant* mock_plant1_;
    MockPlant* mock_plant2_;
    MockPlantProfile* mock_profile1_;
    MockPlantProfile* mock_profile2_;

public:
    explicit TestWaterControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testOpenMainValve();
    void testCloseMainValve();
    void testControlMoistureLevels();
    void testControlUnreagularFlow();
};
