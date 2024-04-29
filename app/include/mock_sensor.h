#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H
#include <cstdlib>
#include <ctime>

#include "sensor.h"

class MockEnvironment {
    float temperature_;
    float humidity_;
    float soil_moisture_;
    float getRandomChange(const float min_change = -2.0, const float max_change = 2.0) {
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
public:
    MockEnvironment(float tmp,float humid, float soil)
        : temperature_(tmp), humidity_(humid), soil_moisture_(soil) {}

    float generateNewTemperature() {
        temperature_ += getRandomChange();
        return temperature_;
    }
    float generateNewHumidity() {
        humidity_ += getRandomChange();
        return humidity_;
    }
    float generateNewSoilMoisture() {
        soil_moisture_ += getRandomChange();
        return soil_moisture_;
    }
};


// Mock sensor classes
class MockSoilMoistureSensor : public SoilMoistureSensor {
private:
    MockEnvironment& mockEnv;

public:
    MockSoilMoistureSensor(MockEnvironment& env)
        : mockEnv(env) {}

    float getMeasurement() override {
        return mockEnv.generateNewSoilMoisture();
    }

    bool calibrate() override {
        // Implement mock calibration logic if needed
        return true;
    }
};

class MockTemperatureSensor : public TemperatureSensor {
private:
    MockEnvironment& mockEnv;

public:
    MockTemperatureSensor(MockEnvironment& env) : mockEnv(env) {}

    float getMeasurement() override {
        return mockEnv.generateNewTemperature();
    }

    bool calibrate() override {
        // Implement mock calibration logic if needed
        return true;
    }
};

class MockHumiditySensor : public HumiditySensor {
private:
    MockEnvironment& mockEnv;

public:
    MockHumiditySensor(MockEnvironment& env) : mockEnv(env) {}

    float getMeasurement() override {
        return mockEnv.generateNewHumidity();
    }

    bool calibrate() override {
        // Implement mock calibration logic if needed
        return true;
    }
};

#endif // MOCK_SENSOR_H
