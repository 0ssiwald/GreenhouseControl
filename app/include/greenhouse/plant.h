#ifndef PLANT_H
#define PLANT_H

#include <QString>
#include <memory>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"
#include "control/sensor.h"
#include "control/water_valve.h"

class Plant {
    // Specify the place of the plant in the plant grid
    int plant_grid_row_number_;
    int plant_grid_column_number_;

    QDateTime  sowing_date_;
    std::shared_ptr<PlantProfile> profile_;
    std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor_;

    std::shared_ptr<WaterValve> water_valve_;
public:
    Plant(const QDateTime&  sowing_date, std::shared_ptr<PlantProfile> profile, int row_number = 0, int column_number = 0) :
        plant_grid_row_number_(row_number), plant_grid_column_number_(column_number), sowing_date_(sowing_date), profile_(profile) {}

    bool savePlantToFile(const QString&);
    void setWaterValve(std::shared_ptr<WaterValve> water_valve) {water_valve_ = water_valve;}
    void setSoilMoistureSensor(std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor) {soil_moisture_sensor_ = soil_moisture_sensor;};
    void setGridPosition(int, int);
    int getGridRowNumber() {return plant_grid_row_number_;}
    int getGridColumnNumber() {return plant_grid_column_number_;}
    std::shared_ptr<WaterValve> getWaterValve() {return water_valve_;}
    std::shared_ptr<PlantProfile> getProfile() {return profile_;}
    std::shared_ptr<SoilMoistureSensor> getSoilMoistureSensor() {return soil_moisture_sensor_;}
    std::shared_ptr<PlantProfile> getPlantProfile() {return profile_;}
    QDateTime getSowingDate() {return sowing_date_;}
    friend QDebug operator<<(QDebug qdebug, const Plant &pl);
};

#endif // PLANT_H
