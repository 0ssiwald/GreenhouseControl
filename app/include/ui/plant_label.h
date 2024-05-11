#ifndef PLANT_LABEL_H
#define PLANT_LABEL_H
#include <QLabel>
#include "sensor.h"

class PlantLabel: public QLabel {
    Q_OBJECT
public:
    explicit PlantLabel(std::shared_ptr<SoilMoistureSensor> moisture_sensor = nullptr, QLabel* parent = nullptr)
        : QLabel(parent), moisture_sensor_(moisture_sensor) {}
    void setMoistureSensor(std::shared_ptr<SoilMoistureSensor> sensor) {moisture_sensor_ = sensor;}
    std::shared_ptr<SoilMoistureSensor> getMoistureSensor() {return moisture_sensor_;}
    void setPlantLabelLayout();
private:
    std::shared_ptr<SoilMoistureSensor> moisture_sensor_;
};
#endif // PLANT_LABEL_H
