#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <string>
#include <vector>
#include "plant_group.h"

class Greenhouse {

public:
    int number_of_group_rows;
    int number_of_group_columns;
    std::vector<PlantGroup*> plant_groups;

    ~Greenhouse() {
        for (auto plant_group : plant_groups) {
            delete plant_group;
        }
    }
    PlantGroup createPlantGroup();
    bool saveGreehouse();
    bool loadGreenhouseFromFile(const std::string&);
    friend std::ostream &operator<<(std::ostream &, const Greenhouse &);
    std::string displayGreenhouse();
    PlantGroup* getPlantGroup();

};

#endif // GREENHOUSE_H
