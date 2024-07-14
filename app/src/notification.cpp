#include "notification.h"
#include "date_time.h"
#include <sstream>

// Builds a notification String that can be displayed from the attributes of the notification
std::string Notification::getNotificationMessage() {
    std::ostringstream notification_stream;
    notification_stream << "Woche " << (week_index_ + 1) << " Gruppe " << group_name_ << ":\n";

    std::ostringstream plant_numbers_stream;
    if (plant_names_.size() > 1) {
        plant_numbers_stream << "n";
    }
    for (auto it = plant_names_.begin(); it != plant_names_.end(); ++it) {
        plant_numbers_stream << " " << *it;
        if (it != plant_names_.end() - 1) {
            plant_numbers_stream << ",";
        }
    }
    std::string plant_numbers_string = plant_numbers_stream.str();

    switch (notification_type_) {
    case NotificationTypes::LampDistanceNotification:
        notification_stream << "Der optimale Lampenabstand der Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << " cm";
        break;
    case NotificationTypes::FertilizerNotification:
        if(plant_names_.size() == 1)
            notification_stream << "Die Pflanze" << plant_numbers_string << " muss gedüngt werden mit:\n" << value_as_string_;
        else
            notification_stream << "Die Pflanze" << plant_numbers_string << " müssen gedüngt werden mit:\n" << value_as_string_;
        break;
    case NotificationTypes::TemperatureNotification:
        notification_stream << "Die optimale Temperatur der Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << " °C";
        break;
    case NotificationTypes::HumidityNotification:
        notification_stream << "Die optimale Luftfeuchtigkeit der Pflanze" << plant_numbers_string << " beträgt " << value_as_string_ << "%";
        break;
    default:
        notification_stream << "Unknown notification";
        break;
    }

    return notification_stream.str();
}

// so that similar plants in a plant group have the same notification
bool Notification::isNotificationTheSameForAnotherPlant(std::chrono::system_clock::time_point time_point, int week_index, std::string group_name,
                                          std::string value_as_string, NotificationTypes notification_type) {
    if (DateTimeConverter::isSameDay(time_point, activation_timepoint_) && week_index_ == week_index &&
        value_as_string_ == value_as_string && notification_type_ == notification_type &&
        group_name_ == group_name) {
        return true;
    }
    return false;
}
