#include "greenhouse/condition.h"
#include <sstream>

// Add a fertilizer to the fertilizer vector
void Condition::addFertilizer(std::shared_ptr<Fertilizer> fertilizer, int amount) {
    fertilizers_.emplace_back(fertilizer, amount);
    return;
}

// Erase the Notification from the notification vector
void Condition::removeNotification(NotificationTypes notification) {
    notifications_.erase(std::remove(notifications_.begin(), notifications_.end(), notification), notifications_.end());
}


std::string Condition::getFertilazersAsString() {
    std::ostringstream fertilizer_string_combined;
    for (auto it = fertilizers_.begin(); it != fertilizers_.end(); ++it) {
        std::string fertilizer_name = it->getFertilizer()->getName();
        std::string fertilizer_amount = std::to_string(it->getAmount()) + " ml";
        std::string fertilizer_type = "(" + it->getFertilizer()->getType() + ")";
        std::string fertilizer_string = fertilizer_name + " " + fertilizer_amount + " " + fertilizer_type;

        fertilizer_string_combined << fertilizer_string;
        if (it != fertilizers_.end() - 1) {
            fertilizer_string_combined << "\n";
        }
    }
    return fertilizer_string_combined.str();
}
