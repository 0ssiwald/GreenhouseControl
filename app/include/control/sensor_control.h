#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <memory>
#include <QObject>
#include "sensor.h"
#include "greenhouse/greenhouse.h"
//#include "mock_enviroment.h"


class SensorControl: public QObject {
    Q_OBJECT
    std::shared_ptr<Sensor> temperature_sensor_;
    std::shared_ptr<Greenhouse> greenhouse_;
    std::shared_ptr<Sensor> humidity_sensor_;
public:
    explicit SensorControl(std::shared_ptr<Greenhouse>);
    void addSoilSensorsToPlants();
    std::shared_ptr<Sensor> getTemperatureSensor() {return temperature_sensor_;}
    std::shared_ptr<Sensor> getHumiditySensor() {return humidity_sensor_;}
public slots:
    void measureTemperature();
    void measureHumidity();
    void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);
    void soilMoisturesMeasured();

};

#endif // SENSOR_CONTROL_H
