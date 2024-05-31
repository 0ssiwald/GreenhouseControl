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


void NotificationControl::createAllNotificationsForAllPlants(std::shared_ptr<Greenhouse> greenhouse) {
    for(auto & group: greenhouse->getPlantGroups()) {
        std::string group_name = group->getGroupName();
        for(auto &plant: group->getPlants()) {
            std::string plant_name = plant->getPlantName();
            std::chrono::system_clock::time_point sowing_date = plant->getSowingDate();
            int week_index = 0;
            for(auto &condition: plant->getProfile()->getConditionsWeekly()) {
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






/*
void NotificationControl::updateActiveNotificationList() {
    bool notifcation_list_has_changed = false;
    // Current time to compare it to the sowing dates
    //QDateTime current_time = QDateTime::currentDateTime();
    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();

    for(size_t group_index = 0; group_index < greenhouse_->getPlantGroups().size(); group_index++) {
        for(size_t plant_index = 0; plant_index < greenhouse_->getPlantGroups()[group_index]->getPlants().size(); plant_index++) {
            std::shared_ptr<Plant> plant = greenhouse_->getPlantGroups()[group_index]->getPlants()[plant_index];
            // Calculates the time in weeks between now and sowing date
            std::chrono::hours elapsed_hours = std::chrono::duration_cast<std::chrono::hours>(plant->getSowingDate() - current_time);
            size_t time_diff_in_weeks = elapsed_hours.count() / (24 * 7);
            for(size_t week_index = 0; week_index < plant->getProfile()->getConditionsWeekly().size(); week_index++) {
                // only took at the weeks that are already happened
                if(week_index <= time_diff_in_weeks) {
                    for(auto &notification_type: plant->getProfile()->getConditionsWeekly()[week_index]->getNotificationTypes()) {
                        std::string value_as_string;
                        switch(notification_type) {
                        case NotificationTypes::LampDistanceNotification:
                            value_as_string = plant->getProfile()->getConditionsWeekly()[week_index]->getLampDistance();
                            break;
                        case NotificationTypes::FertilizerNotification:
                            value_as_string = plant->getProfile()->getConditionsWeekly()[week_index]->getFertilazersAsString();
                            break;
                        case NotificationTypes::TemperatureNotification:
                            value_as_string = plant->getProfile()->getConditionsWeekly()[week_index]->getTemperature();
                            break;
                        case NotificationTypes::HumidityNotification:
                            value_as_string = plant->getProfile()->getConditionsWeekly()[week_index]->getHumidity();
                            break;
                        default:
                            value_as_string = "Something went wrong";
                        }
                        if(addNewNotificationToActiveList(group_index, plant_index, week_index, value_as_string, notification_type)) {
                            notifcation_list_has_changed = true;
                        }
                    }
                }
            }
        }
    }
    // Update the UI only if at least one notification has changed
    if(notifcation_list_has_changed) {
        emit updateNotificationListInUi();
    }
}

// Add a Notification if its new or else update the plant vector -> return true
bool NotificationControl::addNewNotificationToActiveList(int group_index, int plant_index, int week_index, std::string value_as_string, NotificationTypes notification_type) {
    // If there are already plants with the same conditions just the additional plant number is saved
    for(auto & notification: active_notification_list_) {
        if(notification->getValueAsString() == value_as_string
            && notification->getGroupNumber() == int(group_index)
            && notification->getNotificationType() == notification_type
            && notification->getWeekNumber() == int(week_index)) {
            for(auto &plant_number: notification->getPlantNumbers()) {
                if(plant_number == plant_index) {
                    return false;
                }
            }
            notification->addPlantNumber(int(plant_index));
            return true;
        }
    }
    // If not add the new notification to the active list
    std::shared_ptr<Notification> notification;
    notification = std::make_shared<Notification>(int(group_index), int(plant_index), int( week_index), value_as_string, notification_type);
    active_notification_list_.push_back(notification);

    return true;
}



// Displays notification for debugging
void NotificationControl::displayNotifications() {
    for(auto &note: active_notification_list_) {
        qDebug() << note->getNotificationMessage();
    }
}
*/
