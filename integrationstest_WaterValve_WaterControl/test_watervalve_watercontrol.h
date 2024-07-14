#include <QtTest>
#include "sensors_actors/water_valve.h"
#include "sensors_actors/water_control.h"

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
    MockPlant(MockPlantProfile* mock_profile, WaterValve* water_valve, Sensor* mock_sensor) : mock_profile_(mock_profile), water_valve_(water_valve), mock_sensor_(mock_sensor) {}
    std::string getPlantName() override {return "Test";}
    MockPlantProfile* getPlantProfile() override {return mock_profile_;}
    WaterValve* getWaterValve() override {return water_valve_;}
    Sensor* getSoilSensor() override {return mock_sensor_;}
};



class TestWaterValveWaterControl : public QObject {
    Q_OBJECT

    WaterControl *water_control_;
    WaterValve* water_valve_;
    FlowSensor* mock_sensor_;
    Greenhouse* mock_greenhouse_;

    MockPlant* mock_plant1_;
    MockPlant* mock_plant2_;
    MockPlantProfile* mock_profile1_;
    MockPlantProfile* mock_profile2_;

public:
    explicit TestWaterValveWaterControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testOpenMainValve();
    void testCloseMainValve();
    void testControlMoistureLevels_1();
    void testControlMoistureLevels_2();
};
