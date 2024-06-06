#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <memory>
#include <chrono>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"

class Plant {
    std::string plant_name_;
    // Specify the place of the plant in the plant grid
    int plant_grid_row_number_;
    int plant_grid_column_number_;

    std::chrono::system_clock::time_point  sowing_date_;
    std::shared_ptr<PlantProfile> profile_;
public:
    Plant(const std::string & name, const std::chrono::system_clock::time_point&  sowing_date, std::shared_ptr<PlantProfile> profile, int row_number = 0, int column_number = 0) :
        plant_name_(name), plant_grid_row_number_(row_number), plant_grid_column_number_(column_number), sowing_date_(sowing_date), profile_(profile) {}
    // For mocking????
    Plant();
    virtual ~Plant() = default;

    bool savePlantToFile(const std::string&);
    void setGridPosition(int, int);
    int getGridRowNumber() {return plant_grid_row_number_;}
    int getGridColumnNumber() {return plant_grid_column_number_;}
    std::string getPlantName() {return plant_name_;}
    std::shared_ptr<PlantProfile> getProfile() {return profile_;}
    std::shared_ptr<PlantProfile> getPlantProfile() {return profile_;}
    std::chrono::system_clock::time_point  getSowingDate() {return sowing_date_;}
    friend QDebug operator<<(QDebug qdebug, const Plant &pl);
};

#endif // PLANT_H
