#include "greenhouse/greenhouse.h"

bool Greenhouse::addPlantGroupToGrid(PlantGroup* pg, unsigned int row_position, unsigned int column_position) {
    // Check plant group pointer is nullptr
    if(!pg) {
        return false;
    }
    // Check viability of row and column numbers
    if (row_position > number_of_group_rows_ || column_position > number_of_group_columns_) {
        qWarning() << "group cant be added to desired row";
        return false;
    }
    for(auto &it: plant_groups_) {
        if(it->getGridRowNumber() == row_position && it->getGridColumnNumber() == column_position) {
            qWarning() << "group cant be added to desired column";
            return false;
        }
    }
    pg->setGridPosition(row_position, column_position);
    plant_groups_.push_back(pg);
    return true;
}

void Greenhouse::setGroupGridSize(unsigned int row_size, unsigned int column_size) {
    number_of_group_rows_ = row_size;
    number_of_group_columns_ = column_size;
}

std::vector<Plant*> Greenhouse::getAllPlants() {
    std::vector<Plant*> plant_vector;
    for(auto& group: plant_groups_) {
        for(auto& plant: group->getPlants()) {
            plant_vector.push_back(plant);
        }
    }
    return plant_vector;
}

