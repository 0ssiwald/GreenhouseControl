#include "control/sensor_control.h"

#include "control/sensor.h"
#include "control/mock_enviroment.h"
#include <QtDebug>


void SensorControl::addSoilSensor(std::shared_ptr<Sensor> sensor) {
    soil_sensors_.push_back(sensor);
}

void SensorControl::addSensors(MockEnvironment& mockEnv) {
    // Add mock sensors
    //sensors.push_back(std::make_shared<MockSoilMoistureSensor>(mockEnv, 0.0f, 100.0f));
    temperature_sensor_ = std::make_shared<TemperatureSensor>(mockEnv);
    //temperature_sensor_->addMockEnviroment(mockEnv);
    humidity_sensor_ = std::make_shared<HumiditySensor>(mockEnv);
    //humidity_sensor_->addMockEnviroment(mockEnv);
}

void SensorControl::measureTemperature() {
    float temperature = temperature_sensor_->getMeasurement();
    // Create a formatted QString using the desired precision and fixed-point format
    QString formattedTemperature = QString::asprintf("Temperature: %.1f °C", temperature);
    // Save the temperature to the log without " " but with ° by UTF-8 encoding
    const QByteArray utf8EncodedMessage = formattedTemperature.toUtf8();
    qInfo() << utf8EncodedMessage.constData();


    //Emit a signal for the UI
    emit temperatureMeasured(temperature);
}

void SensorControl::measureHumidity() {
    float humidity = humidity_sensor_->getMeasurement();
    // Create a formatted QString using the desired precision and fixed-point format
    QString formattedHumidity = QString::asprintf("Temperature: %.1f °C", humidity);
    // Save the humidity to the log
    const QByteArray utf8EncodedMessage = formattedHumidity.toUtf8();
    qInfo() << utf8EncodedMessage.constData();

    emit humidityMeasured(humidity);
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
