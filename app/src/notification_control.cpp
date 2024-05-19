#include "notification_control.h"


NotificationControl::NotificationControl(std::shared_ptr<Greenhouse> greenhouse, int time_between_checks_in_s)
    : QObject(nullptr), time_between_checks_in_s_(time_between_checks_in_s), greenhouse_(greenhouse) {}


void NotificationControl::updateNotificationList() {
    bool notifcation_list_has_changed = false;
    // Clear the notification list first
    //std::vector<std::shared_ptr<Notification>> notification_list_old = active_notification_list_;
    //active_notification_list_.clear();
    // Current time to compare it to the sowing dates
    QDateTime current_time = QDateTime::currentDateTime();
    for(size_t group_index = 0; group_index < greenhouse_->getPlantGroups().size(); group_index++) {
        for(size_t plant_index = 0; plant_index < greenhouse_->getPlantGroups()[group_index]->getPlants().size(); plant_index++) {
            std::shared_ptr<Plant> plant = greenhouse_->getPlantGroups()[group_index]->getPlants()[plant_index];
            // Calculates the time in weeks between now and sowing date
            size_t time_diff_in_secs = plant->getSowingDate().secsTo(current_time);
            size_t time_diff_in_weeks = time_diff_in_secs / (60 * 60 * 24 * 7);
            for(size_t week_index = 0; week_index < plant->getProfile()->getConditionsWeekly().size(); week_index++) {
                // only took at the weeks that are already happened
                if(week_index <= time_diff_in_weeks) {
                    for(auto &notification_type: plant->getProfile()->getConditionsWeekly()[week_index]->getNotificationTypes()) {
                        QString value_as_string;
                        switch(notification_type) {
                        case NotificationTypes::LampDistanceNotification:
                            value_as_string = QString::number(plant->getProfile()->getConditionsWeekly()[week_index]->getLampDistance());
                            break;
                        case NotificationTypes::FertilizerNotification:
                            value_as_string = plant->getProfile()->getConditionsWeekly()[week_index]->getFertilazersAsString();
                            break;
                        case NotificationTypes::TemperatureNotification:
                            value_as_string = QString::number(plant->getProfile()->getConditionsWeekly()[week_index]->getTemperature());
                            break;
                        case NotificationTypes::HumidityNotification:
                            value_as_string = QString::number(plant->getProfile()->getConditionsWeekly()[week_index]->getHumidity());
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
bool NotificationControl::addNewNotificationToActiveList(int group_index, int plant_index, int week_index, QString value_as_string, NotificationTypes notification_type) {
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
    std::shared_ptr<Notification> notification;
    notification = std::make_shared<Notification>(int(group_index), int(plant_index), int( week_index), value_as_string, notification_type);
    active_notification_list_.push_back(notification);

    return true;
}

// Deletes Notification from active List and from the Plant
void NotificationControl::deleteNotification(int notification_index) {
    std::shared_ptr<Notification> notification = active_notification_list_[notification_index];
    int plant_group_index = (notification->getGroupNumber());
    int week_index = (notification->getWeekNumber());
    for(size_t plant_index = 0; plant_index < notification->getPlantNumbers().size(); plant_index++) {
        std::shared_ptr<Condition> condition = greenhouse_->getPlantGroups()[plant_group_index]->getPlants()[plant_index]->getPlantProfile()->getConditionsWeekly()[week_index];
        for(auto notification_type: condition->getNotificationTypes()) {
            if(notification_type == notification->getNotificationType()) {
                condition->removeNotification(notification_type);
            }
        }
    }
    active_notification_list_.erase(active_notification_list_.begin() + notification_index);
}

void NotificationControl::displayNotifications() {
    for(auto &note: active_notification_list_) {
        qDebug() << note->getNotificationMessage();
    }
}
