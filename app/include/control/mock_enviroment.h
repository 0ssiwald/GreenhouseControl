#ifndef MOCK_ENVIROMENT_H
#define MOCK_ENVIROMENT_H



class MockEnvironment {
    //float temperature_;
    //float humidity_;
    float getRandomChange(const float min_change = -0.5, const float max_change = 0.5);
public:
    //MockEnvironment(float tmp,float humid)
   //     : temperature_(tmp), humidity_(humid) {}


    float generateNewTemperature(float last_temperature) {
        float new_temperature = last_temperature + getRandomChange();
        return new_temperature;
    }
    float generateNewHumidity(float last_humidity) {
        float new_humidity = last_humidity + getRandomChange();
        return new_humidity;
    }
    float generateNewSoilMoisture(float soil_moisture, float max_dry_amount = 1.0) {
        float new_soil_moisture = soil_moisture - getRandomChange(0, max_dry_amount);
        return new_soil_moisture;
    }
};

#endif // MOCK_ENVIROMENT_H
