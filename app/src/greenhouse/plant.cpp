#include "greenhouse/plant.h"

unsigned int Plant::getGridRowNumber() {return plant_grid_row_number_;}
unsigned int Plant::getGridColumnNumber() {return plant_grid_column_number_;}

void Plant::setGridPosition(unsigned int row_number,unsigned int column_number) {
    plant_grid_row_number_ = row_number;
    plant_grid_column_number_ = column_number;
}
