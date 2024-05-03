#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include <vector>
#include <memory>
#include "sensor_control.h"
#include "log.h"
#include "greenhouse/greenhouse.h"

class WaterValve {
public:
    void openValve();
    void closeValve();
};

class WaterControl {
    int time_between_moisture_control_in_s;
    std::vector<std::shared_ptr<WaterValve>> water_valves;
    std::shared_ptr<WaterValve> main_valve;
    FlowSensor *flow_sensor;
    SensorControl *sensors;
    SystemLog log;
    Greenhouse *greenhouse;
public:
    bool shutOffMainValve();
    bool openMainValve();
    bool waterPlant();
    void controlMoistureLevels();
};

#endif // WATER_CONTROL_H
