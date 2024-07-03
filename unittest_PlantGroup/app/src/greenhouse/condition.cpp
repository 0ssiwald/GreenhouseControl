#include "greenhouse/condition.h"
#include <sstream>

std::string Condition::getFertilazersAsString() {
    std::ostringstream fertilizer_string_combined;
    for (auto it = fertilizers_.begin(); it != fertilizers_.end(); ++it) {
        std::string fertilizer_name = it->getFertilizer()->getName();
        std::string fertilizer_amount = std::to_string(it->getAmount()) + " ml";
        std::string fertilizer_type = "(" + it->getFertilizer()->getType() + ")";
        std::string fertilizer_string = fertilizer_name + " " + fertilizer_amount + " " + fertilizer_type;

        fertilizer_string_combined << fertilizer_string;
        // Add a \n after every fertilizer component exept the last one
        if (it != fertilizers_.end() - 1) {
            fertilizer_string_combined << "\n";
        }
    }
    return fertilizer_string_combined.str();
}


// Add a fertilizer to the fertilizer vector
void Condition::addFertilizer(Fertilizer* fertilizer, int amount) {fertilizers_.emplace_back(fertilizer, amount);}
