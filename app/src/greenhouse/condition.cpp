#include "greenhouse/condition.h"

// Add a fertilizer to the fertilizer vector
void Condition::addFertilizer(std::shared_ptr<Fertilizer> fertilizer, int amount) {
    fertilizers_.emplace_back(fertilizer, amount);
    return;
}

// Erase the Notification from the notification vector
void Condition::removeNotification(NotificationTypes notification) {
    notifications_.erase(std::remove(notifications_.begin(), notifications_.end(), notification), notifications_.end());
}

// Get the fertilazer as one combined QString
QString Condition::getFertilazersAsString() {
    QString fertilizer_string_combined;
    for(auto &it: fertilizers_) {
        QString fertilizer_name = QString(it.getFertilizer()->getName());
        QString fertilizer_amount = QString("%1 ml").arg(QString::number(it.getAmount()));
        QString fertilizer_type = QString("(%1)").arg(it.getFertilizer()->getType());
        QString fertilizer_string = QString("%1 %2 %3").arg(fertilizer_name, fertilizer_amount, fertilizer_type);
        if(&it != &fertilizers_.back()) {
            fertilizer_string += "\n";
        }
        fertilizer_string_combined += fertilizer_string;
    }
    return fertilizer_string_combined;
}