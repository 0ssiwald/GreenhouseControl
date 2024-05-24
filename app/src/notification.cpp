#include "notification.h"
#include <sstream>

std::string Notification::getNotificationMessage() {
    std::ostringstream notification_stream;
    notification_stream << "Woche " << (week_index_ + 1) << " Gruppe " << (group_index_ + 1) << ":\n";

    std::ostringstream plant_numbers_stream;
    if (plant_indices_.size() > 1) {
        plant_numbers_stream << "n";
    }
    for (auto it = plant_indices_.begin(); it != plant_indices_.end(); ++it) {
        plant_numbers_stream << " " << (*it + 1);
        if (it != plant_indices_.end() - 1) {
            plant_numbers_stream << ",";
        }
    }
    std::string plant_numbers_string = plant_numbers_stream.str();

    switch (notification_type_) {
    case NotificationTypes::LampDistanceNotification:
        notification_stream << "Der optimale Lampenabstand für Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << " cm";
        break;
    case NotificationTypes::FertilizerNotification:
        notification_stream << "Die Pflanze" << plant_numbers_string << " müssen gedüngt werden mit:\n" << value_as_string_;
        break;
    case NotificationTypes::TemperatureNotification:
        notification_stream << "Die optimale Temperatur für Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << " °C";
        break;
    case NotificationTypes::HumidityNotification:
        notification_stream << "Die optimale Luftfeuchtigkeit für Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << "%";
        break;
    default:
        notification_stream << "Unknown notification";
        break;
    }

    return notification_stream.str();
}
