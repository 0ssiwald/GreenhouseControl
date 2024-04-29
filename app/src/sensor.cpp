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
    // Bestimmt nicht gut so dass measure temperature mit dem Ui so zusammen ist
    window_.getUi()->temperatureLabel->setText(QString("Temperatur: %1 °C").arg(QString::number(temperature, 'f', 1))); // 'f', 1 -> eine Nachkommastelle
    //qDebug() << "Temperature: " << temperature << "°C";
}

void SensorControl::measureHumidity() {
    float humidity = humidity_sensor_->getMeasurement();
    // Bestimmt nicht gut so dass measure temperature mit dem Ui so zusammen ist
    window_.getUi()->humidityLabel->setText(QString("Luftfeuchtigkeit: %1%").arg(QString::number(humidity, 'f', 1))); // 'f', 1 -> eine Nachkommastelle
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
