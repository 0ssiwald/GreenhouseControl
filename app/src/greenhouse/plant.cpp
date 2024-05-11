#include "greenhouse/plant.h"
#include <QDateTime>
//#include "date_time.h"

QDebug operator<<(QDebug qdebug, const Plant &pl) {
    // Specify the desired format for the output string
    qdebug << "Sowing Date: " << pl.sowing_date_.toString("dd.MM.yyyy HH:mm:ss") << Qt::endl;
    return qdebug;
}


void Plant::setGridPosition(int row_number, int column_number) {
    plant_grid_row_number_ = row_number;
    plant_grid_column_number_ = column_number;
}