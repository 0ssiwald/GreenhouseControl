#include "testmockenvironment.h"

FlowSensor* mock_sensor;
WaterValve* water_valve;
Plant* mock_plant;
float sensor_value = 5.0;
bool valve_is_open = true;
bool flow_detected = false;

const float epsilon = 1.0e-4;   // fixed epsilon for comparison of float numbers

float Sensor::getMeasurement() {
    return sensor_value;
}

void Sensor::setMeasurent(float measurement_value) {
    sensor_value = measurement_value;
}
bool FlowSensor::isFlowDetected() {
    return flow_detected;
}

Sensor* SensorControl::getTemperatureSensor() {
    return mock_sensor;
}
Sensor* SensorControl::getHumiditySensor() {
    return mock_sensor;
}
// slots need implementation even when not used
void SensorControl::measureTemperature() {}
void SensorControl::measureHumidity() {}
void SensorControl::measureSoilMoistures() {}
void WaterControl::controlMoistureLevels() {}

void WaterValve::openValve() {
    valve_is_open = true;
}

void WaterValve::closeValve() {
    valve_is_open = false;
}

bool WaterValve::getValveIsOpen() {
    return valve_is_open;
}

void TestMockEnvironment::init() {}

void TestMockEnvironment::cleanup() {}

void TestMockEnvironment::initTestCase() {
    mock_sensor = new FlowSensor;
    water_valve = new WaterValve;
    mock_plant = new MockPlant(water_valve, mock_sensor);
    sensor_control_ = new SensorControl(mock_sensor, mock_sensor, nullptr);
    water_control_ = new WaterControl(water_valve, mock_sensor, nullptr);
    sut = new MockEnvironment(sensor_control_, water_control_);
}

void TestMockEnvironment::cleanupTestCase() {
    delete mock_sensor;
    delete water_valve;
    delete mock_plant;
    delete sensor_control_;
    delete water_control_;
    delete sut;
}


void TestMockEnvironment::testGetRandomChange() {
    float change = sut->getRandomChange(1.0, 3.0);
    // Test that getRandomChange returns a value within the specified range
    QVERIFY(change > 1.0 && change < 3.0);
    // for one nagitive
    change = sut->getRandomChange(-1.0, 3.0);
    QVERIFY(change > -1.0 && change < 3.0);
    // for two negative
    change = sut->getRandomChange(-3.0, -1.0);
    QVERIFY(change > -3.0 && change < -1.0);

}
void TestMockEnvironment::testGenerateNewTemperature() {
    sensor_value = 5.0;
    sut->generateNewTemperature();
    QVERIFY(sensor_value > 4.5);
    QVERIFY(sensor_value < 5.5);
    QVERIFY(sensor_value != 5.0);

}
void TestMockEnvironment::testGenerateNewHumidity() {
    sensor_value = 5.0;
    sut->generateNewHumidity();
    QVERIFY(sensor_value > 4.0);
    QVERIFY(sensor_value < 6.0);
    QVERIFY(sensor_value != 5.0);

}
void TestMockEnvironment::testGenerateNewSoilMoisture() {
    sensor_value = 5.0;
    // Test for reducing soil moisture if valve is open
    sut->generateNewSoilMoisture(mock_plant);
    QVERIFY(sensor_value > 4.0);
    QVERIFY(sensor_value < 5.0);
    // Test for increasing soil mosture if plant gets watered
    flow_detected = true;
    sensor_value = 5.0;
    sut->generateNewSoilMoisture(mock_plant);
    QVERIFY(sensor_value > 5.0);
    QVERIFY(sensor_value < 8.0);

}
void TestMockEnvironment::testGenerateNewFlow() {
    // test increasing flow with open valve
    sensor_value = 5.0;
    sut->generateNewFlow(water_valve);
    QVERIFY((sensor_value - 8.0) <= epsilon);
}

QTEST_APPLESS_MAIN(TestMockEnvironment);

