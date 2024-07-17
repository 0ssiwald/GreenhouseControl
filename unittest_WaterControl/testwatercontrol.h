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
    WaterValve* water_valve_;
    Sensor* mock_sensor_;
    MockPlant(MockPlantProfile* mock_profile, WaterValve* mock_valve, Sensor* mock_sensor) : mock_profile_(mock_profile), water_valve_(mock_valve), mock_sensor_(mock_sensor) {}
    std::string getPlantName() override {return "Test";}
    MockPlantProfile* getPlantProfile() override {return mock_profile_;}
    WaterValve* getWaterValve() override {return water_valve_;}
    Sensor* getSoilSensor() override {return mock_sensor_;}
};
class MockValve: public WaterValve {
public:
    MockValve() = default;
    bool open_valve_ = false;
    void openValve() override {open_valve_ = true;}
    void closeValve()override {open_valve_ = false;}
    bool getValveIsOpen() override {return open_valve_;}

};

class TestWaterControl : public QObject {
    Q_OBJECT

    WaterControl *sut;
    WaterValve* mock_main_valve_;
    FlowSensor* mock_sensor_;
    Greenhouse* mock_greenhouse_;

    MockPlant* mock_plant1_;
    WaterValve* mock_valve1_;
    WaterValve* mock_valve2_;
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
    void testControlUnreagularFlow();
    // Tests with control flow method
    void testControlMoistureLevels_no_plants();
    void testControlMoistureLevels_one_dry_plant();
    void testControlMoistureLevels_one_wet_plant();
    void testControlMoistureLevels_one_watered_plant();
    void testControlMoistureLevels_two_plants();

};
