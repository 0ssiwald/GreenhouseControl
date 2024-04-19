#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <chrono>
#include "plant_profile.h"

class Plant {
    std::chrono::system_clock::time_point sowing_date;
    PlantProfile* profile;
public:
    Plant(const std::chrono::system_clock::time_point& sowing_date, PlantProfile* profile) :
        sowing_date(sowing_date), profile(profile) {}

    ~Plant() {
        delete profile;
    }
    bool savePlantToFile(const std::string&);
    PlantProfile getPlantProfile();
    void addPlantProfile();
};

#endif // PLANT_H
