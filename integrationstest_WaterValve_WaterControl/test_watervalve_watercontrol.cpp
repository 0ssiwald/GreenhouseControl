#include "test_watervalve_watercontrol.h"

float sensor_value = 5.0;
float water_threshold;
bool flow_detected = false;
std::vector<Plant*> mock_plants;

// Reimplementation of methods for mocks
float Sensor::getMeasurement() {
    return sensor_value;
}
bool FlowSensor::isFlowDetected() {
    return flow_detected;
}
std::vector<Plant*> Greenhouse::getAllPlants() {
    return mock_plants;
}
void TestWaterValveWaterControl::init() {
    flow_detected = false;
    water_control_ = new WaterControl(water_valve_, mock_sensor_, mock_greenhouse_);
}

void TestWaterValveWaterControl::cleanup() {
    delete water_control_;
    water_valve_->closeValve();
}

void TestWaterValveWaterControl::initTestCase() {
    mock_sensor_ = new FlowSensor;
    water_valve_ = new WaterValve;
    mock_profile1_ = new MockPlantProfile;
    mock_plant1_ = new MockPlant(mock_profile1_, water_valve_, mock_sensor_);
    mock_plants.push_back(mock_plant1_);
    mock_profile2_ = new MockPlantProfile;
    mock_plant2_ = new MockPlant(mock_profile2_, water_valve_, mock_sensor_);
    mock_plants.push_back(mock_plant2_);
    mock_greenhouse_ = new Greenhouse;


}

void TestWaterValveWaterControl::cleanupTestCase() {
    delete mock_plant1_;
    delete mock_profile1_;
    delete mock_plant2_;
    delete mock_profile2_;
    delete mock_greenhouse_;
    delete mock_sensor_;
    delete water_valve_;
}

//tests
void TestWaterValveWaterControl::testOpenMainValve() {
    water_valve_->closeValve();
    QSignalSpy spy = QSignalSpy(water_control_, SIGNAL(updateFlow(WaterValve*)));

    water_control_->openMainValve();

    QVERIFY(water_valve_->getValveIsOpen() == true);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == water_valve_);

}
void TestWaterValveWaterControl::testCloseMainValve() {
    water_valve_->openValve();
    QSignalSpy spy = QSignalSpy(water_control_, SIGNAL(updateFlow(WaterValve*)));

    water_control_->closeMainValve();

    QVERIFY(water_valve_->getValveIsOpen() == false);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == water_valve_);

}
// Test for opening the valve
void TestWaterValveWaterControl::testControlMoistureLevels_1() {
    QSignalSpy spyFlow(water_control_, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(water_control_, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 6.0;
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_profile2_->mock_lower_threshold_ = 3.0;
    mock_profile2_->mock_upper_threshold_ = 9.0;
    QCOMPARE(water_valve_->getValveIsOpen(), false);

    water_control_->controlMoistureLevels();
    // Test the opening of valves
    // Test if the secound plant opend the valve and only one valve has opend
    QCOMPARE(water_valve_->getValveIsOpen(), true);
    QCOMPARE(water_control_->getNumberOfOpenValves(), 1);
    QCOMPARE(spyFlow.count(), 1); // One valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled
}
// Test for closing of the valve
void TestWaterValveWaterControl::testControlMoistureLevels_2() {
    mock_profile1_->mock_lower_threshold_ = 6.0;
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_profile2_->mock_lower_threshold_ = 3.0;
    mock_profile2_->mock_upper_threshold_ = 4.0;
    water_valve_->openValve();

    //Test for closing the secound valve
    water_control_->controlMoistureLevels();
    QCOMPARE(water_valve_->getValveIsOpen(), false);
}

QTEST_APPLESS_MAIN(TestWaterValveWaterControl)
