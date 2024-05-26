#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include <QObject>
#include <QtDebug>
#include <memory>
#include <map>
#include "water_valve.h"
#include "sensor.h"
#include "sensor_control.h"
#include "greenhouse/greenhouse.h"

class WaterControl: public QObject {
    Q_OBJECT
    int number_of_open_valves_ = 0;
    std::shared_ptr<WaterValve> main_valve_;
    std::shared_ptr<FlowSensor> flow_sensor_;
    std::shared_ptr<Greenhouse> greenhouse_;
    SensorControl* sensor_control_;
    std::map<std::shared_ptr<Plant>, std::shared_ptr<WaterValve>> plants_with_water_valves_;
    void controlUnregularFlow();
public:
    explicit WaterControl(std::shared_ptr<Greenhouse>, SensorControl *);

    void addWaterValves();
    bool isMainValveOpen() {return main_valve_->getValveIsOpen();}
    void openMainValve() {main_valve_->openValve();}
    void closeMainValve() {main_valve_->closeValve();}
    std::shared_ptr<FlowSensor> getFlowSensor() {return flow_sensor_;}
    std::map<std::shared_ptr<Plant>, std::shared_ptr<WaterValve>> getWaterValves() {return plants_with_water_valves_;}

public slots:
    void controlMoistureLevels();

signals:
    void mainValveWasClosed();
    void updateFlow(std::shared_ptr<WaterValve>);
    void moistureLevelsControled();
};

#endif // WATER_CONTROL_H
