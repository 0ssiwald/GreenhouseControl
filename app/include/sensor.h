#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>
#include <memory>

#include "log.h"

class Sensor {
protected:
    float current_measurement;
public:
    // virtual destuctor to enshure that derived classes get destroyed
    virtual ~Sensor() = default;
    // can be overritten by derived classes
    virtual float getValue() const;
    // must be overritten by derived classes
    virtual bool calibrate() = 0;
};

class SoilMoistureSensor: public Sensor {
    float dry_calibration_value;
    float wet_calibration_value;
public:
    SoilMoistureSensor(float dry, float wet)
        : dry_calibration_value(dry), wet_calibration_value(wet) {}
    void loadCalibration(std::string file_name="calibration.csv");
    virtual bool calibrate() override {
        // Implement calibration logic here
        return true;
    }
};


class TemperatureSensor: public Sensor {
    virtual bool calibrate() override {
        // Implement calibration logic here
        return true;
    }
};
class HumiditySensor: public Sensor {
    virtual bool calibrate() override {
        // Implement calibration logic here
        return true;
    }
};
class FlowSensor: public Sensor {
    virtual bool calibrate() override {
        // Implement calibration logic here
        return true;
    }
    // signal FlowSignal() ?????
};


class SensorControl {
    int measurements_per_minute;
    std::vector<std::shared_ptr<Sensor>> sensors;
    std::shared_ptr<SystemLog> system_log;
public:
    SensorControl(std::shared_ptr<SystemLog> log, int measurements_per_minute = 1)
        : measurements_per_minute(measurements_per_minute), system_log(log) {}
    float takeMeasurement();
    void saveToLog();
    void addSensor(std::shared_ptr<Sensor>);
};

#endif // SENSOR_H
