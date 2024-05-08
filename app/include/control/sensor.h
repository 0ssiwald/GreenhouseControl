#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <memory.h>
#include "mock_enviroment.h"

class Sensor {
protected:
     std::shared_ptr<MockEnvironment> mock_enviroment_;
    float measurement_value_;
public:
    Sensor(std::shared_ptr<MockEnvironment> mock_env, float initial_value)
        : mock_enviroment_(mock_env), measurement_value_(initial_value) {}
    // virtual destuctor to enshure that derived classes get destroyed
    virtual ~Sensor() = default;
    // must be overritten by derived classes
    virtual void takeMeasurement() = 0;
    virtual bool calibrate() = 0;
    float getMeasurementValue() {return measurement_value_;};
};

class SoilMoistureSensor: public Sensor {
public:
    SoilMoistureSensor(std::shared_ptr<MockEnvironment> mock_env, float initial_value = 70.0)
        : Sensor(mock_env, initial_value) {}
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual void takeMeasurement() override {
        measurement_value_ = mock_enviroment_->generateNewSoilMoisture(measurement_value_);
    }
};

class TemperatureSensor: public Sensor {
public:
    TemperatureSensor(std::shared_ptr<MockEnvironment> mock_env, float initial_value = 20.0)
        : Sensor(mock_env, initial_value) {}
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual void takeMeasurement() override {
        measurement_value_ = mock_enviroment_->generateNewTemperature(measurement_value_);
    }
};
class HumiditySensor: public Sensor {
public:
    HumiditySensor(std::shared_ptr<MockEnvironment> mock_env, float initial_value = 60.0)
        : Sensor(mock_env, initial_value) {}
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual void takeMeasurement() override {
        measurement_value_ = mock_enviroment_->generateNewHumidity(measurement_value_);
    }
};
class FlowSensor: public Sensor {
public:
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual void takeMeasurement() override {
        throw("Not implemented");
    }
    // signal FlowSignal() ?????
};

#endif // SENSOR_H
