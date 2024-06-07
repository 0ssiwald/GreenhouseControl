#include "greenhouse/plant.h"

void Plant::setGridPosition(unsigned int row_number,unsigned int column_number) {
    plant_grid_row_number_ = row_number;
    plant_grid_column_number_ = column_number;
}
