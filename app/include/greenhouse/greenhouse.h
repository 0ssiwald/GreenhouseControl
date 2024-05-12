#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <vector>
#include <memory>
#include <QtDebug>
#include "plant_group.h"
#include "note.h"


class Greenhouse {
    // Specify the grid size for the plant group grid in the greenhouse
    int number_of_group_rows_;
    int number_of_group_columns_;

    std::vector<std::shared_ptr<PlantGroup>> plant_groups_;
public:
    Greenhouse(int row_size = 0, int column_size = 0)
        : number_of_group_rows_(row_size), number_of_group_columns_(column_size) {}

    int getNumberOfRows() {return number_of_group_rows_;};
    int getNumberOfColumns() {return number_of_group_columns_;};
    void setGroupGridSize(int, int);
    bool saveGreehouse();
    void addPlantGroupToGrid(std::shared_ptr<PlantGroup>, int, int);
    std::vector<std::shared_ptr<PlantGroup>> getPlantGroups() {return plant_groups_;};
    friend QDebug operator<<(QDebug, const Greenhouse &);
};



// Class to create Greenhouse form File
// At the moment just created in code
class GreenhouseCreate {
    std::shared_ptr<Greenhouse> greenhouse;
public:
    std::shared_ptr<Greenhouse> createGreenhouseFromCode();
    // for later
    std::shared_ptr<Greenhouse> loadGreenhouseFromFile(const std::string&);
};

#endif // GREENHOUSE_H
