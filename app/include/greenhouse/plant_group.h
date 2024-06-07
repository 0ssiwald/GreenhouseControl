#ifndef PLANT_GROUP_H
#define PLANT_GROUP_H

#include <vector>
#include <QDebug>
#include "plant.h"
#include "note.h"

class PlantGroup {
    std::string group_name_;
    // Specify the place of the plant group in the greenhouse grid
    unsigned int group_grid_row_number_;
    unsigned int group_grid_column_number_;
    // Specify the grid size for the plants in the plant group
    unsigned int number_of_plant_rows_;
    unsigned int number_of_plant_columns_;
    std::vector<Plant*> plants_;
    std::vector<Note*> notes_;
public:
    PlantGroup(const std::string &name, unsigned int row_size = 0, unsigned int column_size = 0)
        : group_name_(name), number_of_plant_rows_(row_size), number_of_plant_columns_(column_size) {}

    // for mocking in tests
    PlantGroup() = default;
    virtual ~PlantGroup() = default;

    unsigned int getGridRowNumber();
    unsigned int getGridColumnNumber();
    unsigned int getNumberOfPlantRows() {return number_of_plant_rows_;}
    unsigned int getNumberOfPlantColumns() {return number_of_plant_columns_;}
    std::string getGroupName() {return group_name_;}
    std::vector<Note*> getNotes() {return notes_;}
    std::vector<Plant*> getPlants();
    void setPlantGridSize(unsigned int, unsigned int);
    void setGridPosition(unsigned int , unsigned int);
    void addPlantToGrid(Plant*, unsigned int, unsigned int);
    void addNote(Note* );
    void removeNote(size_t);
    void removePlant(Plant*);
};

#endif // PLANT_GROUP_H
