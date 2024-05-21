#ifndef PLANT_LABEL_H
#define PLANT_LABEL_H
#include <QLabel>
#include "control/sensor.h"
#include "control/water_valve.h"

class PlantLabel: public QLabel {
    Q_OBJECT
public:
    explicit PlantLabel(std::shared_ptr<SoilMoistureSensor> moisture_sensor = nullptr, std::shared_ptr<WaterValve> water_valve = nullptr, QLabel* parent = nullptr)
        : QLabel(parent), moisture_sensor_(moisture_sensor), water_valve_(water_valve) {}
    void setMoistureSensor(std::shared_ptr<SoilMoistureSensor> sensor) {moisture_sensor_ = sensor;}
    void setWaterValve(std::shared_ptr<WaterValve> water_valve) {water_valve_ = water_valve;}
    void setPlantLabelLayout();
    void updatePlantLabel(bool);
private:
    std::shared_ptr<SoilMoistureSensor> moisture_sensor_;
    std::shared_ptr<WaterValve> water_valve_;

};
#endif // PLANT_LABEL_H
