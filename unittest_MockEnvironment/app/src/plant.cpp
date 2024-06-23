#include "plant.h"
#include "date_time.h"

QDebug operator<<(QDebug qdebug, const Plant &pl) {
    qdebug << "Sowing Date: " << DateTimeConverter::timePointToString(pl.sowing_date) << Qt::endl;
    return qdebug;
}
