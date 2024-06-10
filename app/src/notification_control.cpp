#include "notification_control.h"
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

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
    for(auto & notification: impending_notifications_) {
        if(notification->isNotificationTheSameForAnotherPlant(time_point, week_index, group_name, value_as_string, notification_type)) {
            notification->addPlant(plant_name);
            return;
        }
    }
    // If not add the new notification to the active list
    std::shared_ptr<Notification> notification;
    notification = std::make_shared<Notification>(time_point, week_index, group_name, plant_name, value_as_string, notification_type);
    impending_notifications_.push_back(notification);
    return;
}

// Deletes Notification from active List and from the Plant
void NotificationControl::deleteNotification(int notification_index) {
    std::shared_ptr<Notification> notification = active_notification_list_[notification_index];
    qInfo().noquote() << "Diese Benachrichtigung wurde gelöscht:\n" << notification->getNotificationMessage();
    active_notification_list_.erase(active_notification_list_.begin() + notification_index);
}

