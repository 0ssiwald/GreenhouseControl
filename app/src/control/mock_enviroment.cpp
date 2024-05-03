#include "control/mock_enviroment.h"

#include <cstdlib>
#include <ctime>

float MockEnvironment::getRandomChange(const float min_change, const float max_change) {
    // Seed the random number generator with the current time
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    // Generate a random value between kMinChange and kMaxChange
    float randomChange = min_change + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max_change - min_change)));
    return randomChange;
}
