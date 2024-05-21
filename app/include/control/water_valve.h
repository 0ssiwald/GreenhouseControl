#ifndef WATER_VALVE_H
#define WATER_VALVE_H

class WaterValve {
    bool valve_is_open_;
public:
    WaterValve(bool valve_is_open = false)
        : valve_is_open_(valve_is_open) {}
    void openValve() {valve_is_open_ = true;}
    void closeValve() {valve_is_open_ = false;}
    bool getValveIsOpen() {return valve_is_open_;}
};

#endif // WATER_VALVE_H
