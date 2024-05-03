#include <vector>
#include "greenhouse/plant_group.h"

void PlantGroup::addPlant(std::shared_ptr<Plant> plant) {
    //Temporary way to add plants just to columns no plant rows at the moment
    number_of_plant_rows = 1;
    number_of_plant_columns += 1;
    plants.push_back(plant);
    return;
}

QDebug operator<<(QDebug qdebug, const PlantGroup &pg) {
    qdebug << "number_of_group_rows: " << pg.number_of_plant_rows << Qt::endl;
    qdebug << "number_of_group_columns: " << pg.number_of_plant_columns << Qt::endl;
    qdebug << "there are " << pg.plants.size() << " plants and " << pg.notes.size() << " notes" << Qt::endl << Qt::endl;
    int i = 1;
    for(auto& it: pg.plants) {
        qdebug << "Plant" << i << Qt::endl;
        qdebug << *it << Qt::endl;
        i++;
    }
    return qdebug;
}
