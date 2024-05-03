#ifndef MOCK_ENVIROMENT_H
#define MOCK_ENVIROMENT_H



class MockEnvironment {
    float temperature_;
    float humidity_;
    float soil_moisture_;
    float getRandomChange(const float min_change = -0.5, const float max_change = 0.5);
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

#endif // MOCK_ENVIROMENT_H
