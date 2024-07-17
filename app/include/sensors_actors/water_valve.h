#ifndef WATER_VALVE_H
#define WATER_VALVE_H

class WaterValve {
protected:
    bool valve_is_open_;
public:
    WaterValve(bool valve_is_open = false)
        : valve_is_open_(valve_is_open) {};

    // For Mock classes for testing
    virtual ~WaterValve() = default;

    virtual void openValve() {valve_is_open_ = true;}
    virtual void closeValve() {valve_is_open_ = false;}
    virtual bool getValveIsOpen() {return valve_is_open_;}
};

#endif // WATER_VALVE_H
