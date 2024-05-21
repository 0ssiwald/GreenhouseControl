#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include <QObject>
#include <QtDebug>
#include <memory>
#include "water_valve.h"
#include "sensor.h"
#include "greenhouse/greenhouse.h"

class WaterControl: public QObject {
    Q_OBJECT
    int number_of_open_valves_;
    std::shared_ptr<WaterValve> main_valve_;
    std::shared_ptr<FlowSensor> flow_sensor_;
    std::shared_ptr<Greenhouse> greenhouse_;
public:
    explicit WaterControl(std::shared_ptr<Greenhouse>);

    void addWaterValvesToPlants();
    bool isMainValveOpen() {return main_valve_->getValveIsOpen();}
    void openMainValve() {main_valve_->openValve();}
    void closeMainValve() {main_valve_->closeValve();}
    std::shared_ptr<FlowSensor> getFlowSensor() {return flow_sensor_;}

public slots:
    void controlMoistureLevels();
    void controlUnregularFlow();

signals:
    void mainValveWasClosed();
};

#endif // WATER_CONTROL_H
