#include "control/sensor_control.h"
#include "control/sensor.h"
#include <QtDebug>

SensorControl::SensorControl(std::vector<std::shared_ptr<Plant>> plants)
    : QObject(nullptr) {

    temperature_sensor_ = std::make_shared<TemperatureSensor>();
    humidity_sensor_ = std::make_shared<HumiditySensor>();
    addSoilSensors(plants);
}


void SensorControl::addSoilSensors(std::vector<std::shared_ptr<Plant>> plants) {
    for(auto& plant: plants) {
        std::shared_ptr<SoilMoistureSensor> soil_sensor = std::make_shared<SoilMoistureSensor>();
        plants_with_soil_moisture_sensors_.insert_or_assign(plant, soil_sensor);
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
    QString soil_moistures_string = "Soil Moistures of Plants: ";
    for(auto& plant_and_sensor: plants_with_soil_moisture_sensors_) {
        QString plant_name = QString::fromStdString(plant_and_sensor.first->getPlantName());
        emit updateSoilMoisture(plant_and_sensor.first);
        float sensor_value = plant_and_sensor.second->getMeasurement();
        soil_moistures_string += QString("%1: %2 ").arg(plant_name, QString::number(sensor_value));   
    }
    // Save the soil moisture to the log
    qInfo().noquote() << soil_moistures_string;
    emit soilMoisturesMeasured();
}
