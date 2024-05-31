#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <memory.h>

class Sensor {
protected:
    float measurement_value_;
public:
    explicit Sensor(float initial_value)
        : measurement_value_(initial_value) {}
    // virtual destuctor to enshure that derived classes get destroyed
    virtual ~Sensor() = default;
    float getMeasurement() {return measurement_value_;};
    void setMeasurent(float measurement_value) {measurement_value_ = measurement_value;}
};

class SoilMoistureSensor: public Sensor {
public:
    SoilMoistureSensor(float initial_value = 70.0)
        : Sensor(initial_value) {}
};

class TemperatureSensor: public Sensor {
public:
    TemperatureSensor(float initial_value = 20.0)
        : Sensor(initial_value) {}
};
class HumiditySensor: public Sensor {
public:
    HumiditySensor(float initial_value = 60.0)
        : Sensor(initial_value) {}
};
class FlowSensor: public Sensor {
    // Every value over the theshold is considered a flow of water
    float flow_threshold_ = 2;
public:
    FlowSensor(float initial_value = 0.0)
        : Sensor(initial_value) {}

    bool isFlowDetected() {
        if(measurement_value_ > flow_threshold_) {
            return true;
        }
        return false;
    }
};

#endif // SENSOR_H
