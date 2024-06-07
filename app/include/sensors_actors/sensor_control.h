#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <QObject>
#include "sensors_actors/sensor.h"
#include "greenhouse/greenhouse.h"


class SensorControl: public QObject {
    Q_OBJECT
    Sensor* temperature_sensor_;
    Sensor* humidity_sensor_;
    Greenhouse* greenhouse_;
public:
    explicit SensorControl( Sensor* temperature_sensor, Sensor* humidity_sensor, Greenhouse* greenhouse)
        : QObject(nullptr), temperature_sensor_(temperature_sensor), humidity_sensor_(humidity_sensor), greenhouse_(greenhouse) {}

    Sensor* getTemperatureSensor() {return temperature_sensor_;}
    Sensor* getHumiditySensor() {return humidity_sensor_;}
public slots:
    void measureTemperature();
    void measureHumidity();
    void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);
    void soilMoisturesMeasured();
    void updateSoilMoisture(Plant*);

};

#endif // SENSOR_CONTROL_H
