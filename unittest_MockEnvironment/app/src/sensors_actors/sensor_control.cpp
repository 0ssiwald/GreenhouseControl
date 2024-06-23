#include "sensors_actors/sensor_control.h"
#include <QtDebug>

Sensor* SensorControl::getTemperatureSensor() {
    return temperature_sensor_;
}
Sensor* SensorControl::getHumiditySensor() {
    return humidity_sensor_;
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
    for(auto& plant: greenhouse_->getAllPlants()) {
        QString plant_name = QString::fromStdString(plant->getPlantName());
        emit updateSoilMoisture(plant);
        float sensor_value = plant->getSoilSensor()->getMeasurement();
        soil_moistures_string += QString("%1: %2 ").arg(plant_name, QString::number(sensor_value));   
    }
    // Save the soil moisture to the log
    qInfo().noquote() << soil_moistures_string;
    emit soilMoisturesMeasured();
}
