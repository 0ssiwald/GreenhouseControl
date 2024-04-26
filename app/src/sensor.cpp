#include "sensor.h"
#include "mock_sensor.h"

void SensorControl::addSoilSensor(std::shared_ptr<Sensor> sensor) {
    soil_sensors_.push_back(sensor);
}

void SensorControl::addMockSensors(MockEnvironment& mockEnv) {
    // Add mock sensors
    //sensors.push_back(std::make_shared<MockSoilMoistureSensor>(mockEnv, 0.0f, 100.0f));
    temperature_sensor_ = std::make_shared<MockTemperatureSensor>(mockEnv);
    humidity_sensor_ = std::make_shared<MockHumiditySensor>(mockEnv);
}

float SensorControl::measureTemperature() {
    return temperature_sensor_->getMeasurement();
}
float SensorControl::measureHumidity() {
    return humidity_sensor_->getMeasurement();
}
