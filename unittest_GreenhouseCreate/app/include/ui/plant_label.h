#ifndef PLANT_LABEL_H
#define PLANT_LABEL_H
#include <QLabel>
#include "sensors_actors/sensor.h"
#include "sensors_actors/water_valve.h"

class PlantLabel: public QLabel {
    Q_OBJECT
public:
    explicit PlantLabel(Sensor* moisture_sensor = nullptr, WaterValve* water_valve = nullptr, QLabel* parent = nullptr)
        : QLabel(parent), moisture_sensor_(moisture_sensor), water_valve_(water_valve) {}
    void setMoistureSensor(Sensor* sensor) {moisture_sensor_ = sensor;}
    void setWaterValve(WaterValve* water_valve) {water_valve_ = water_valve;}
    void setPlantLabelLayout();
    void updatePlantLabel(bool, bool);
private:
    Sensor* moisture_sensor_;
    WaterValve* water_valve_;

};
#endif // PLANT_LABEL_H
