#include "testwatercontrol.h"

bool valve_is_open = false;
float sensor_value = 5.0;
float water_threshold;
bool flow_detected = false;
std::vector<Plant*> mock_plants;

// Reimplementation of methods
void WaterValve::openValve() {
    valve_is_open = true;
}

void WaterValve::closeValve() {
    valve_is_open = false;
}

bool WaterValve::getValveIsOpen() {
    return valve_is_open;
}

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
    valve_is_open = false;
    flow_detected = false;
}

void TestWaterControl::cleanup() {}

void TestWaterControl::initTestCase() {
    mock_sensor_ = new FlowSensor;
    mock_valve_ = new WaterValve;
    mock_profile1_ = new MockPlantProfile;
    mock_plant1_ = new MockPlant(mock_profile1_, mock_valve_, mock_sensor_);
    mock_plants.push_back(mock_plant1_);
    mock_profile2_ = new MockPlantProfile;
    mock_plant2_ = new MockPlant(mock_profile2_, mock_valve_, mock_sensor_);
    mock_plants.push_back(mock_plant2_);
    mock_greenhouse_ = new Greenhouse;

    sut = new WaterControl(mock_valve_, mock_sensor_, mock_greenhouse_);
}

void TestWaterControl::cleanupTestCase() {
    delete sut;
    delete mock_plant1_;
    delete mock_profile1_;
    delete mock_plant2_;
    delete mock_profile2_;
    delete mock_greenhouse_;
    delete mock_sensor_;
    delete mock_valve_;
}


//tests
void TestWaterControl::testOpenMainValve() {
    valve_is_open = false;
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(updateFlow(WaterValve*)));

    sut->openMainValve();

    QVERIFY(valve_is_open == true);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == mock_valve_);

}
void TestWaterControl::testCloseMainValve() {
    valve_is_open = true;
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(updateFlow(WaterValve*)));

    sut->closeMainValve();

    QVERIFY(valve_is_open == false);
    QVERIFY(spy.count() == 1);    // one signal emitted
    // Test if the right object was emitted
    WaterValve* emitted_valve = qvariant_cast<WaterValve*>(spy.takeFirst().at(0));
    QVERIFY(emitted_valve == mock_valve_);

}
void TestWaterControl::testControlMoistureLevels() {
    QSignalSpy spyFlow(sut, SIGNAL(updateFlow(WaterValve*)));
    QSignalSpy spyMoisture(sut, SIGNAL(moistureLevelsControled()));
    mock_profile1_->mock_lower_threshold_ = 6.0;
    mock_profile1_->mock_upper_threshold_ = 9.0;
    mock_profile2_->mock_lower_threshold_ = 3.0;
    mock_profile2_->mock_upper_threshold_ = 9.0;
    QCOMPARE(valve_is_open, false);

    sut->controlMoistureLevels();
    // Test the opening of valves
    // Test if the secound plant opend the valve and only one valve has opend
    QCOMPARE(valve_is_open, true);
    QCOMPARE(sut->getNumberOfOpenValves(), 1);
    QCOMPARE(spyFlow.count(), 1); // One valve should have changed state
    QCOMPARE(spyMoisture.count(), 1); // Moisture levels should be controlled

    //Test for closing the secound valve
    mock_profile2_->mock_upper_threshold_ = 4.0;
    sut->controlMoistureLevels();
    QCOMPARE(valve_is_open, false);
    QCOMPARE(sut->getNumberOfOpenValves(), 0);
    QCOMPARE(spyFlow.count(), 2); // another one be emitted now
    QCOMPARE(spyMoisture.count(), 2);
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


QTEST_APPLESS_MAIN(TestWaterControl);


