#include "sensor.h"
#include "mock_sensor.h"
#include <QtDebug>

void SensorControl::addSoilSensor(std::shared_ptr<Sensor> sensor) {
    soil_sensors_.push_back(sensor);
}

void SensorControl::addMockSensors(MockEnvironment& mockEnv) {
    // Add mock sensors
    //sensors.push_back(std::make_shared<MockSoilMoistureSensor>(mockEnv, 0.0f, 100.0f));
    temperature_sensor_ = std::make_shared<MockTemperatureSensor>(mockEnv);
    humidity_sensor_ = std::make_shared<MockHumiditySensor>(mockEnv);
}

void SensorControl::measureTemperature() {
    float temperature = temperature_sensor_->getMeasurement();
    emit temperatureMeasured(temperature);
    //qDebug() << "Temperature: " << temperature << "°C";
}

void SensorControl::measureHumidity() {
    float humidity = humidity_sensor_->getMeasurement();
    emit humidityMeasured(humidity);
    //qDebug() << "Humidity: " << humidity_sensor_->getMeasurement() << "%";
}

/*
float SensorControl::measureSoilMoistures() {
    // Implementation goes here
    return 0.5;
}

void SensorControl::setLog() {
    // Implementation goes here
}

*/
