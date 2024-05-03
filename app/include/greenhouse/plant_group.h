#ifndef PLANT_GROUP_H
#define PLANT_GROUP_H

#include <string>
#include <vector>
#include <memory>
#include <QDebug>
#include "plant.h"
#include "note.h"

class PlantGroup {
    //int number_of_plants;
    int number_of_plant_rows;
    int number_of_plant_columns;
    std::vector<std::shared_ptr<Plant>> plants;
    std::vector<std::shared_ptr<Note>> notes;
public:
    PlantGroup(int rows = 0, int columns = 0)
        : number_of_plant_rows(rows), number_of_plant_columns(columns) {}

    void addPlant(std::shared_ptr<Plant>);
    void removePlant(std::shared_ptr<Plant>);
    bool savePlantGroupToFile(const std::string&);
    std::string displayPlantGroup();
    std::shared_ptr<Plant> getPlant(int plant_nr);
    friend QDebug operator<<(QDebug, const PlantGroup &);
};

#endif // PLANT_GROUP_H
