#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <string>
#include <vector>
#include <memory>
#include <QtDebug>
#include "plant_group.h"


class Greenhouse {

public:
    int number_of_group_rows;
    int number_of_group_columns;
    std::vector<std::shared_ptr<PlantGroup>> plant_groups;
    Greenhouse(int rows = 0, int columns = 0)
        : number_of_group_rows(rows), number_of_group_columns(columns) {}
/*
    ~Greenhouse() {
        for (auto plant_group : plant_groups) {
            delete plant_group;
        }
    }
*/
    PlantGroup createPlantGroup();
    bool saveGreehouse();
    friend QDebug operator<<(QDebug, const Greenhouse &);
    std::string displayGreenhouse();
    void addPlantGroup(std::shared_ptr<PlantGroup>);
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
