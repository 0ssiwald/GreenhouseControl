#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <vector>
#include <QtDebug>
#include "plant_group.h"


class Greenhouse {
    // Specify the grid size for the plant group grid in the greenhouse
    unsigned int number_of_group_rows_;
    unsigned int number_of_group_columns_;

    std::vector<PlantGroup*> plant_groups_;
public:
    Greenhouse(unsigned int row_size = 0, unsigned  int column_size = 0)
        : number_of_group_rows_(row_size), number_of_group_columns_(column_size) {}

    unsigned int getNumberOfRows() {return number_of_group_rows_;};
    unsigned int getNumberOfColumns() {return number_of_group_columns_;};
    std::vector<PlantGroup*> getPlantGroups() {return plant_groups_;};
    std::vector<Plant*> getAllPlants();
    void setGroupGridSize(unsigned int, unsigned int);
    bool addPlantGroupToGrid(PlantGroup*, unsigned int, unsigned int);
};

#endif // GREENHOUSE_H
