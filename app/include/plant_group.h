#ifndef PLANT_GROUP_H
#define PLANT_GROUP_H

#include <string>
#include <vector>
#include "plant.h"
#include "note.h"

class PlantGroup {
    int number_of_plants;
    int number_of_plant_rows;
    int number_of_plant_columns;
    std::vector<Plant*> plants;
    std::vector<Note*> notes;
public:
    ~PlantGroup() {
        for (auto plant : plants) {
            delete plant;
        }
    }
    void addPlant(Plant*);
    void removePlant(Plant*);
    bool savePlantGroupToFile(const std::string&);
    std::string displayPlantGroup();
    Plant *getPlant(int plant_nr);
};

#endif // PLANT_GROUP_H
