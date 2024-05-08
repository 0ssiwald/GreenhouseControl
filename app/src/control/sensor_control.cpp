#include "control/sensor_control.h"

#include "control/sensor.h"
#include "control/mock_enviroment.h"
#include <QtDebug>

SensorControl::SensorControl(std::shared_ptr<MockEnvironment> mock_enviroment, std::shared_ptr<Greenhouse> greenhouse, int seconds_per_measurement = 1)
    : QObject(nullptr), seconds_per_measurement_(seconds_per_measurement), greenhouse_(greenhouse), mock_enviroment_(mock_enviroment)  {

    temperature_sensor_ = std::make_shared<TemperatureSensor>(mock_enviroment_);
    humidity_sensor_ = std::make_shared<HumiditySensor>(mock_enviroment_);
}

void SensorControl::addSoilSensorsToPlants() {
    for(auto& group_iterator: greenhouse_->getPlantGroups()) {
        for(auto& plant_iterator: group_iterator->getPlants()) {
            std::shared_ptr<SoilMoistureSensor> soil_sensor = std::make_shared<SoilMoistureSensor>(mock_enviroment_);
            plant_iterator->setSoilMoistureSensor(soil_sensor);
        }
    }
}

void SensorControl::measureTemperature() {
    temperature_sensor_->takeMeasurement();
    float temperature = temperature_sensor_->getMeasurementValue();
    // Create a formatted QString using the desired precision and fixed-point format
    QString formattedTemperature = QString::asprintf("Temperature: %.1f °C", temperature);
    // Save the temperature to the log without " " but with ° by UTF-8 encoding
    const QByteArray utf8EncodedMessage = formattedTemperature.toUtf8();
    qInfo() << utf8EncodedMessage.constData();

    //Emit a signal for the UI
    emit temperatureMeasured(temperature);
}

void SensorControl::measureHumidity() {
    humidity_sensor_->takeMeasurement();
    float humidity = humidity_sensor_->getMeasurementValue();
    // Create a formatted QString using the desired precision and fixed-point format
    QString formattedHumidity = QString::asprintf("Humidity: %.1f%%", humidity);
    qInfo().noquote() << formattedHumidity;

    emit humidityMeasured(humidity);
}

void  SensorControl::measureSoilMoistures() {
    int group_number = 1;
    for(auto& group_iterator: greenhouse_->getPlantGroups()) {
        QString soil_moistures_string = QString::asprintf("Soil Moisture of Plant Group %i:", group_number);
        for(auto& plant_iterator: group_iterator->getPlants()) {
            std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor = plant_iterator->getSoilMoistureSensor();
            soil_moisture_sensor->takeMeasurement();
            float soil_moisture = soil_moisture_sensor->getMeasurementValue();
            soil_moistures_string.append(QString::asprintf(" %.1f", soil_moisture));
        }
        // Save the humidity to the log
        qInfo().noquote() << soil_moistures_string;
        group_number++;
    }
    emit soilMoisturesMeasured();
}

