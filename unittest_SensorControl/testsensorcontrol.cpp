#include "testsensorcontrol.h"

const float epsilon = 1.0e-4;   // fixed epsilon for comparison of float numbers

void TestSensorControl::init() {
    mock_temperature_sensor_ = std::make_shared<MockSensor>();
    mock_humidity_sensor_ = std::make_shared<MockSensor>();

    std::shared_ptr<MockPlant> mock_plant1 = std::make_shared<MockPlant>();
    std::shared_ptr<MockSensor> mock_sensor1 = std::make_shared<MockSensor>();
    mock_plants_with_soil_moisture_sensors_.insert_or_assign(mock_plant1, mock_sensor1);
    std::shared_ptr<MockPlant> mock_plant2 = std::make_shared<MockPlant>();
    std::shared_ptr<MockSensor> mock_sensor2 = std::make_shared<MockSensor>();
    mock_plants_with_soil_moisture_sensors_.insert_or_assign(mock_plant2, mock_sensor2);
    std::shared_ptr<MockPlant> mock_plant3 = std::make_shared<MockPlant>();
    std::shared_ptr<MockSensor> mock_sensor3 = std::make_shared<MockSensor>();
    mock_plants_with_soil_moisture_sensors_.insert_or_assign(mock_plant3, mock_sensor3);

    sut = new SensorControl(mock_temperature_sensor_, mock_humidity_sensor_, mock_plants_with_soil_moisture_sensors_);
}

void TestSensorControl::cleanup() {
    delete sut;
    sut = nullptr;
}

void TestSensorControl::initTestCase() {}

void TestSensorControl::cleanupTestCase() {}


QTEST_APPLESS_MAIN(TestSensorControl)



