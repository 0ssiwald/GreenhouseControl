#include "notification.h"

QString Notification::getNotificationMessage() {
    QString notification_string = QString("Woche %1 Gruppe %2:\n").arg(QString::number(week_index_ + 1), QString::number(group_index_ + 1));
    QString plant_numbers_string;
    // Make "Pflanzen" if there are multable plants
    if(plant_indices_.size() > 1) {
        plant_numbers_string += "n";
    }
    for (auto &plant_number: plant_indices_) {
        plant_numbers_string += QString(" %1").arg(QString::number(plant_number + 1));
        // Add a comma if there are still other plants
        if(plant_number !=  plant_indices_.back()) {
            plant_numbers_string += ",";
        }
    }
    switch(notification_type_) {
    case NotificationTypes::LampDistanceNotification:
        notification_string += QString("Der optimale Lampenabstand für Pflanze%1 beträgt %2 cm").arg(plant_numbers_string, value_as_string_);
        break;
    case NotificationTypes::FertilizerNotification:
        notification_string += QString("Die Pflanze%1  müssen gedüngt werden mit:\n%2").arg(plant_numbers_string, value_as_string_);
        break;
    case NotificationTypes::TemperatureNotification:
        notification_string += QString("Die optimale Temperatur für Pflanze%1 beträgt %2 °C").arg(plant_numbers_string, value_as_string_);
        break;
    case NotificationTypes::HumidityNotification:
        notification_string += QString ("Die optimale Luftfeuchtigkeit für Pflanze%1 beträgt %2%").arg(plant_numbers_string, value_as_string_);
        break;
    default:
        notification_string = QString("Unknown notification");
    }
    return notification_string;
}

