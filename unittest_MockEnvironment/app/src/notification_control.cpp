#include "notification_control.h"
#include "date_time.h"
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

#include <iostream>

NotificationControl::NotificationControl()
    : QObject(nullptr) {}

// If the ativation time is now the notification is removed from the notificationsl list and added to the active notifications list
void NotificationControl::updateActiveNotificationList() {
    std::chrono::system_clock::time_point timepoint_now = std::chrono::system_clock::now();
    bool listHasChanged = false;
    for(auto it = impending_notifications_.begin(); it != impending_notifications_.end(); ) {
        if((*it)->getActivationTimepoint() < timepoint_now) {
            active_notification_list_.push_back(*it);
            impending_notifications_.erase(it); // Erase returns the next iterator
            listHasChanged = true;
        } else {
            ++it; // Increment the iterator only if not erasing
        }
    }
    if(listHasChanged){
        emit updateNotificationListInUi();
    }
}

bool NotificationControl::loadNotificationsFromFile(const std::string& file_name) {
    // Create a QFile object with the given file name.
    QFile file(QString::fromStdString(file_name));

    // Try to open the file in read-only mode and as a text file.
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open file.");
        return false;
    }

    // Read all the data from the file into a QByteArray.
    QByteArray jsonData = file.readAll();

    file.close();

    QJsonParseError parseError;

    // Parse the JSON data into a QJsonDocument.
    QJsonDocument document = QJsonDocument::fromJson(jsonData, &parseError);

    // Check if there was a parse error.
    if (parseError.error != QJsonParseError::NoError) {
        qWarning("JSON parse error: %s", qPrintable(parseError.errorString()));
        return false;
    }

    // Check if the JSON document is an array.
    if (!document.isArray()) {
        qWarning("JSON is not an array.");
        return false;
    }

    // Convert the JSON document to a QJsonArray.
    QJsonArray jsonArray = document.array();

    // Iterate over each value in the JSON array.
    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();

        std::string activation_timepoint_str = obj["activation_timepoint"].toString().toStdString();
        std::chrono::system_clock::time_point activation_timepoint = DateTimeConverter::stringToTimePoint(activation_timepoint_str);

        int week_index = obj["week_index"].toInt();
        std::string group_name = obj["group_name"].toString().toStdString();

        QJsonArray plantNamesArray = obj["plant_names"].toArray();
        std::vector<std::string> plant_names;
        for (const QJsonValue& plantNameValue : plantNamesArray) {
            plant_names.push_back(plantNameValue.toString().toStdString());
        }

        std::string value_as_string = obj["value_as_string"].toString().toStdString();
        std::string notification_type_str = obj["notification_type"].toString().toStdString();
        NotificationTypes notification_type;
        if (notification_type_str == "LampDistanceNotification")
            notification_type = NotificationTypes::LampDistanceNotification;
        else if (notification_type_str == "TemperatureNotification")
            notification_type = NotificationTypes::TemperatureNotification;
        else if (notification_type_str == "HumidityNotification")
            notification_type = NotificationTypes::HumidityNotification;
        else if (notification_type_str == "FertilizerNotification")
            notification_type = NotificationTypes::FertilizerNotification;
        else
            return false;

        Notification* notification = new Notification{
            activation_timepoint,
            week_index,
            group_name,
            plant_names,
            value_as_string,
            notification_type
        };

        impending_notifications_.push_back(notification);
    }
    return true;
}

void NotificationControl::createAllNotificationsForAllPlants(Greenhouse* greenhouse) {
    for(auto & group: greenhouse->getPlantGroups()) {
        std::string group_name = group->getGroupName();
        for(auto &plant: group->getPlants()) {
            std::string plant_name = plant->getPlantName();
            std::chrono::system_clock::time_point sowing_date = plant->getSowingDate();
            int week_index = 0;
            for(auto &condition: plant->getPlantProfile()->getConditionsWeekly()) {
                // Create a duration representing the number of weeks
                std::chrono::duration<int, std::ratio<604800>> duration_weeks(week_index); // 1 week = 604800 seconds
                // Get the activation Timepoint by adding the week_index to the sowing date
                std::chrono::system_clock::time_point activation_timepoint = sowing_date + duration_weeks;
                std::string lamp_distance_string = std::to_string(condition->getLampDistance());
                addNotificationToVector(activation_timepoint, week_index, group->getGroupName(),
                                        plant->getPlantName(), lamp_distance_string, NotificationTypes:: LampDistanceNotification);
                std::ostringstream temperature_stream;
                temperature_stream << std::fixed << std::setprecision(1) << condition->getTemperature();
                std::string temperature_string = temperature_stream.str();
                addNotificationToVector(activation_timepoint, week_index, group->getGroupName(),
                                        plant->getPlantName(), temperature_string, NotificationTypes:: TemperatureNotification);
                std::ostringstream humidity_stream;
                humidity_stream << std::fixed << std::setprecision(1) << condition->getHumidity();
                std::string humidity_string = humidity_stream.str();
                addNotificationToVector(activation_timepoint, week_index, group->getGroupName(),
                                        plant->getPlantName(), humidity_string, NotificationTypes:: HumidityNotification);
                std::string fertilizer_string = condition->getFertilazersAsString();
                addNotificationToVector(activation_timepoint, week_index, group->getGroupName(),
                                        plant->getPlantName(), fertilizer_string, NotificationTypes:: FertilizerNotification);
                week_index++;
            }
        }
    }
}

// Add a Notification if its new or else update the plant vector
 void NotificationControl::addNotificationToVector(std::chrono::system_clock::time_point time_point, int week_index, std::string group_name,
                                                  std::string plant_name, std::string value_as_string, NotificationTypes notification_type) {
    // If there are already plants with the same conditions just the additional plant number is saved
    for(auto& notification: impending_notifications_) {
        if(notification->isNotificationTheSameForAnotherPlant(time_point, week_index, group_name, value_as_string, notification_type)) {
            notification->addPlant(plant_name);
            return;
        }
    }
    // If not add the new notification to the list
    Notification* notification;
    std::vector<std::string> plant_name_vector;
    plant_name_vector.push_back(plant_name);
    notification = new Notification(time_point, week_index, group_name, plant_name_vector, value_as_string, notification_type);
    impending_notifications_.push_back(notification);
    return;
}

// Deletes Notification from active List and from the Plant
bool NotificationControl::deleteNotification(unsigned int notification_index) {
    // Test if the index is valid
    if(notification_index+1 > active_notification_list_.size()) {
        return false;
    }
    Notification* notification = active_notification_list_[notification_index];
    qInfo().noquote() << "Diese Benachrichtigung wurde gelöscht:\n" << notification->getNotificationMessage();
    active_notification_list_.erase(active_notification_list_.begin() + notification_index);
    return true;
}

