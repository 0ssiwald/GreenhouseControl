#include <vector>
#include "greenhouse/plant_group.h"

void PlantGroup::addPlantToGrid(std::shared_ptr<Plant> plant, int row_number, int column_number) {
    // Check viability of row and column numbers
    if (row_number > number_of_plant_rows_ || column_number > number_of_plant_columns_) {
        qDebug() << "row  or columm problem plant";
        qDebug() << "Row Number: " << row_number << "Number of Plant Rows: " << number_of_plant_rows_;
        qDebug() << "Col Number: " << column_number << "Number of Plant Col: " << number_of_plant_columns_;


        throw("Plant cant be added"); // Throw needs catch?????????????????????
        return;
    }
    for(auto &it: plants_) {
        if(it->getGridRowNumber() == row_number && it->getGridColumnNumber() == column_number) {
            qDebug() << "plant pos already taken";
            throw("Plant cant be added"); // Throw needs catch?????????????????????
            return;
        }
    }
    plant->setGridPosition(row_number, column_number);
    plants_.push_back(plant);
}

void PlantGroup::setGridPosition(int row_number, int column_number) {
    group_grid_row_number_ = row_number;
    group_grid_column_number_ = column_number;

}

void PlantGroup::setPlantGridSize(int row_size, int column_size) {
    number_of_plant_rows_ = row_size;
    number_of_plant_columns_ = column_size;
}


QDebug operator<<(QDebug qdebug, const PlantGroup &pg) {
    qdebug << "size_of_plant_grid_rows: " << pg.number_of_plant_rows_ << Qt::endl;
    qdebug << "size_of_plant_grid_columns: " << pg.number_of_plant_columns_ << Qt::endl;
    qdebug << "there are " << pg.plants_.size() << " plants and " << pg.notes_.size() << " notes" << Qt::endl << Qt::endl;
    int i = 1;
    for(auto& it: pg.plants_) {
        qdebug << "Plant" << i << Qt::endl;
        qdebug << *it << Qt::endl;
        i++;
    }
    return qdebug;
}
