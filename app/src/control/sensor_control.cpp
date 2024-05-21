#include "control/sensor_control.h"

#include "control/sensor.h"
//#include "control/mock_enviroment.h"
#include <QtDebug>

SensorControl::SensorControl(std::shared_ptr<Greenhouse> greenhouse)
    : QObject(nullptr), greenhouse_(greenhouse)  {

    temperature_sensor_ = std::make_shared<TemperatureSensor>();
    humidity_sensor_ = std::make_shared<HumiditySensor>();
    addSoilSensorsToPlants();
}

void SensorControl::addSoilSensorsToPlants() {
    for(auto& group_iterator: greenhouse_->getPlantGroups()) {
        for(auto& plant_iterator: group_iterator->getPlants()) {
            std::shared_ptr<SoilMoistureSensor> soil_sensor = std::make_shared<SoilMoistureSensor>();
            plant_iterator->setSoilMoistureSensor(soil_sensor);
        }
    }
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
            float soil_moisture = soil_moisture_sensor->getMeasurement();
            soil_moistures_string.append(QString::asprintf(" %.1f", soil_moisture));
        }
        // Save the humidity to the log
        qInfo().noquote() << soil_moistures_string;
        group_number++;
    }
    emit soilMoisturesMeasured();
}

