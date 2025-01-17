#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include <QObject>
#include <QtDebug>
#include "water_valve.h"
#include "greenhouse/greenhouse.h"


class WaterControl: public QObject {
    Q_OBJECT
    int number_of_open_valves_ = 0;
    WaterValve* main_valve_;
    FlowSensor* flow_sensor_;
    Greenhouse* greenhouse_;
public:
    explicit WaterControl(WaterValve* main_valve, FlowSensor* flow_sensor, Greenhouse* greenhouse)
        : QObject(nullptr), main_valve_(main_valve), flow_sensor_(flow_sensor), greenhouse_(greenhouse) {}
    FlowSensor* getFlowSensor() {return flow_sensor_;}
    int getNumberOfOpenValves() {return number_of_open_valves_;}
    WaterValve* getMainValve() {return main_valve_;}
    bool isMainValveOpen() {return main_valve_->getValveIsOpen();}
    void controlUnregularFlow();
    void openMainValve();
    void closeMainValve();

public slots:
    void controlMoistureLevels();

signals:
    void mainValveWasClosed();
    void updateFlow(WaterValve*);
    void moistureLevelsControled();
};

#endif // WATER_CONTROL_H
