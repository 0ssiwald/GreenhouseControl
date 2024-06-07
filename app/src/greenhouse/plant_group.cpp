#include <vector>
#include "greenhouse/plant_group.h"

unsigned int PlantGroup::getGridRowNumber() {return group_grid_row_number_;}
unsigned int PlantGroup::getGridColumnNumber() {return group_grid_column_number_;}
std::vector<Plant*> PlantGroup::getPlants() {return plants_;}

void PlantGroup::addPlantToGrid(Plant* plant,unsigned int row_number,unsigned int column_number) {
    // Check viability of row and column numbers
    if (row_number > number_of_plant_rows_ || column_number > number_of_plant_columns_) {
        qDebug() << "Plant cant be added: row or columm not viable";
        return;
    }
    for(auto &it: plants_) {
        if(it->getGridRowNumber() == row_number && it->getGridColumnNumber() == column_number) {
            qDebug() << "Plant cant be added: plant position already taken";
            return;
        }
    }
    plant->setGridPosition(row_number, column_number);
    plants_.push_back(plant);
}

void PlantGroup::addNote(Note* note) {
    notes_.push_back(note);
}

void PlantGroup::setGridPosition(unsigned int row_number,unsigned int column_number) {
    group_grid_row_number_ = row_number;
    group_grid_column_number_ = column_number;

}

void PlantGroup::setPlantGridSize(unsigned int row_size,unsigned int column_size) {
    number_of_plant_rows_ = row_size;
    number_of_plant_columns_ = column_size;
}

void PlantGroup::removeNote(size_t index) {
    if (index < notes_.size()) {
        notes_.erase(notes_.begin() + index);
    }
}
