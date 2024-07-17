#include "testwatercontrol.h"

float sensor_value = 5.0;
bool flow_detected = false;
std::vector<Plant*> mock_plants;

// Reimplementation of methods
float Sensor::getMeasurement() {
    return sensor_value;
}
bool FlowSensor::isFlowDetected() {
    return flow_detected;
}
std::vector<Plant*> Greenhouse::getAllPlants() {
    return mock_plants;
}
void TestWaterControl::init() {
    flow_detected = false;
    sut = new WaterControl(mock_main_valve_, mock_sensor_, mock_greenhouse_);
}
void TestWaterControl::cleanup() {
    // After each test empty the plants vector
    mock_plants.clear();
    delete sut;
}
void TestWaterControl::initTestCase() {
    mock_sensor_ = new FlowSensor;
    mock_main_valve_ = new MockValve;
    mock_profile1_ = new MockPlantProfile;
    mock_valve1_ = new MockValve;
    mock_plant1_ = new MockPlant(mock_profile1_, mock_valve1_, mock_sensor_);
    mock_profile2_ = new MockPlantProfile;
    mock_valve2_ = new MockValve;
    mock_plant2_ = new MockPlant(mock_profile2_, mock_valve2_, mock_sensor_);
    mock_greenhouse_ = new Greenhouse;
}
void TestWaterControl::cleanupTestCase() {
    delete mock_plant1_;
    delete mock_profile1_;
    delete mock_plant2_;
    delete mock_profile2_;
    delete mock_greenhouse_;
    delete mock_sensor_;
    delete mock_main_valve_;
    delete mock_valve1_;
    delete mock_valve2_;
}


//tests
void TestWaterControl::testOpenMainValve() {
    mock_main_valve_->closeValve();
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(updateFlow(WaterValve*)));

    sut->openMainValve();

    QVERIFY(mock_main_valve_->getValveIsOpen() == true);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == mock_main_valve_);

}
void TestWaterControl::testCloseMainValve() {
    mock_main_valve_->openValve();
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(updateFlow(WaterValve*)));

    sut->closeMainValve();

    QVERIFY(mock_main_valve_->getValveIsOpen() == false);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == mock_main_valve_);

}
void TestWaterControl::testControlUnreagularFlow() {
    QSignalSpy spy(sut, SIGNAL(mainValveWasClosed()));
    sut->controlUnregularFlow();
    // without flow there should be no signal emitted
    QCOMPARE(sut->getNumberOfOpenValves(), 0);
    QVERIFY(!flow_detected);
    QCOMPARE(spy.count(), 0);
    // Now test activation if flow is present
    flow_detected = true;
    sut->controlUnregularFlow();
    QCOMPARE(spy.count(), 1);
}
void TestWaterControl::testControlMoistureLevels_no_plants() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));

    sut->controlMoistureLevels();

    QCOMPARE(sut->getNumberOfOpenValves(), 0);
    QCOMPARE(spyFlow.count(), 0); // No valve should have changed state
    QCOMPARE(spyMoisture.count(), 0); // Moisture levels should not be controlled
}
void TestWaterControl::testControlMoistureLevels_one_dry_plant() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 6.0;
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_plants.push_back(mock_plant1_); // Test with one plant
    mock_valve1_->closeValve();
    mock_main_valve_->openValve();

    sut->controlMoistureLevels();
    // Test the opening of valves
    QCOMPARE(mock_valve1_->getValveIsOpen(), true);
    QCOMPARE(sut->getNumberOfOpenValves(), 1);
    QCOMPARE(spyFlow.count(), 1); // One valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled
}
void TestWaterControl::testControlMoistureLevels_one_wet_plant() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 3.0;
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_plants.push_back(mock_plant1_);
    mock_valve1_->closeValve();
    mock_main_valve_->openValve();

    sut->controlMoistureLevels();
    // Test that the valve stayed closed
    QCOMPARE(mock_valve1_->getValveIsOpen(), false);
    QCOMPARE(sut->getNumberOfOpenValves(), 0);
    QCOMPARE(spyFlow.count(), 0); // No valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled
}
void TestWaterControl::testControlMoistureLevels_one_watered_plant() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 3.0;
    mock_profile1_->mock_upper_threshold_ = 4.0; // over the threshold the valve should close
    mock_plants.push_back(mock_plant1_);
    mock_valve1_->openValve();

    sut->controlMoistureLevels();
    // Test for closing the valve
    QCOMPARE(mock_valve1_->getValveIsOpen(), false);
    QCOMPARE(sut->getNumberOfOpenValves(), -1);
    QCOMPARE(spyFlow.count(), 1); // No valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled
}
void TestWaterControl::testControlMoistureLevels_two_plants() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 6.0; // fist plant should get watered
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_profile2_->mock_lower_threshold_ = 4.0; // secound plant should stop watering
    mock_profile2_->mock_upper_threshold_ = 3.0;
    mock_plants.push_back(mock_plant1_);
    mock_plants.push_back(mock_plant2_);
    mock_valve1_->closeValve();
    mock_valve2_->openValve();
    mock_main_valve_->openValve();

    sut->controlMoistureLevels();
    QCOMPARE(sut->getNumberOfOpenValves(), 0); // 0 because one gets opend and one closed
    QCOMPARE(spyFlow.count(), 2); // Two valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled
}

QTEST_APPLESS_MAIN(TestWaterControl);


