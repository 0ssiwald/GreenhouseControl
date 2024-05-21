#ifndef PLANT_GROUP_H
#define PLANT_GROUP_H

#include <vector>
#include <memory>
#include <QDebug>
#include "plant.h"
#include "note.h"

class PlantGroup {
    // Specify the place of the plant group in the greenhouse grid
    int group_grid_row_number_;
    int group_grid_column_number_;
    // Specify the grid size for the plants in the plant group
    int number_of_plant_rows_;
    int number_of_plant_columns_;
    std::vector<std::shared_ptr<Plant>> plants_;
    std::vector<std::shared_ptr<Note>> notes_;
public:
    PlantGroup(int row_size = 0, int column_size = 0)
        : number_of_plant_rows_(row_size), number_of_plant_columns_(column_size) {}

    int getGridRowNumber() {return group_grid_row_number_;}
    int getGridColumnNumber() {return group_grid_column_number_;}
    int getNumberOfPlantRows() {return number_of_plant_rows_;}
    int getNumberOfPlantColumns() {return number_of_plant_columns_;}
    std::vector<std::shared_ptr<Note>> getNotes() {return notes_;}
    std::vector<std::shared_ptr<Plant>> getPlants() {return plants_;}
    void setPlantGridSize(int, int);
    void setGridPosition(int , int);
    void addPlantToGrid(std::shared_ptr<Plant>, int, int);
    void addNote(std::shared_ptr<Note>);
    void removeNote(size_t);
    void removePlant(std::shared_ptr<Plant>);
    friend QDebug operator<<(QDebug, const PlantGroup &);
};

#endif // PLANT_GROUP_H
