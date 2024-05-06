#include "greenhouse/plant.h"
#include <QDateTime>
//#include "date_time.h"

QDebug operator<<(QDebug qdebug, const Plant &pl) {
    // Specify the desired format for the output string
    qdebug << "Sowing Date: " << pl.sowing_date.toString("dd.MM.yyyy HH:mm:ss") << Qt::endl;
    return qdebug;
}
