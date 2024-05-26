#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <memory>
#include <QObject>
#include <map>
#include "sensor.h"
#include "greenhouse/greenhouse.h"


class SensorControl: public QObject {
    Q_OBJECT
    std::shared_ptr<Sensor> temperature_sensor_;
    std::shared_ptr<Greenhouse> greenhouse_;
    std::shared_ptr<Sensor> humidity_sensor_;
    std::map<std::shared_ptr<Plant>, std::shared_ptr<Sensor>> plants_with_soil_moisture_sensors_;

public:
    explicit SensorControl(std::shared_ptr<Greenhouse>);
    void addSoilSensors();
    std::shared_ptr<Sensor> getTemperatureSensor() {return temperature_sensor_;}
    std::shared_ptr<Sensor> getHumiditySensor() {return humidity_sensor_;}
    std::map<std::shared_ptr<Plant>, std::shared_ptr<Sensor>> getSoilSensors() {return plants_with_soil_moisture_sensors_;}
public slots:
    void measureTemperature();
    void measureHumidity();
    void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);
    void soilMoisturesMeasured();
    void updateSoilMoisture(std::shared_ptr<Plant>);

};

#endif // SENSOR_CONTROL_H
