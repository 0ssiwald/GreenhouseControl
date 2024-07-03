#ifndef WATER_VALVE_H
#define WATER_VALVE_H

class WaterValve {
    bool valve_is_open_;
public:
    WaterValve(bool valve_is_open = false)
        : valve_is_open_(valve_is_open) {}
    void openValve();
    void closeValve();
    bool getValveIsOpen();
};

#endif // WATER_VALVE_H
