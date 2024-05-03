#include "control/sensor_control.h"

#include "control/sensor.h"
#include "control/mock_enviroment.h"
#include <QtDebug>
#include <chrono>
#include <sstream>
#include <iomanip>  // Needed for std::fixed and std::setprecision

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
    // Create a String for the SystemLog
    std::ostringstream logMessageStream;
    logMessageStream << "Temperature: " << std::fixed << std::setprecision(1) << temperature << " °C";
    std::string logMessage = logMessageStream.str();
    system_log_->saveMessageToLog(logMessage, std::chrono::system_clock::now());
    //Emit a signal for the UI
    emit temperatureMeasured(temperature);
}

void SensorControl::measureHumidity() {
    float humidity = humidity_sensor_->getMeasurement();
    // Create a String for the SystemLog
    std::ostringstream logMessageStream;
    logMessageStream << "Luftfeuchtigkeit: " << std::fixed << std::setprecision(1) << humidity << "%";
    std::string logMessage = logMessageStream.str();
    system_log_->saveMessageToLog(logMessage, std::chrono::system_clock::now());

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
