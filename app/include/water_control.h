#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include <vector>
#include "sensor.h"
#include "log.h"
#include "greenhouse.h"

class WaterValve {
public:
    void openValve();
    void closeValve();
};

class WaterControl {
    int time_between_moisture_control_in_s;
    std::vector<WaterValve*> water_valves;
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
