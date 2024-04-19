#ifndef SENSOR_H
#define SENSOR_H


#include <vector>
#include <string>

#include "log.h"

class Sensor {
protected:
    float *current_measurement; // Als Pointer??
public:
    virtual ~Sensor() {} // virtual destuctor damit bei delete(child) auch die child destructoren aufgerufen werden?
    float getValue();
    bool calibrate();
};

class SoilMoistureSensor: public Sensor {
    float dry_calibration_value;
    float wet_calibration_value;
public:
    SoilMoistureSensor(float dry, float wet)
        : dry_calibration_value(dry), wet_calibration_value(wet) {}
    void loadCalibration(std::string file_name="calibration.csv");
};

class TemperatureSensor: public Sensor {
};
class HumiditySensor: public Sensor {
};
class FlowSensor: public Sensor {
    // signal FlowSignal() ?????
};


class SensorControl {
    // active Class????
    int measurements_per_minute;
    std::vector<Sensor*> sensors; // als Vector von Pointern??
    SystemLog *system_log;
public:
    SensorControl(SystemLog *log, int measurements_per_minute = 1)
        : measurements_per_minute(measurements_per_minute), system_log(log) {}
    float takeMeasurement();
    void saveToLog();
};

#endif // SENSOR_H
