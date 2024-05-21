#ifndef MOCK_ENVIROMENT_H
#define MOCK_ENVIROMENT_H

#include <QObject>
#include "greenhouse/greenhouse.h"
#include "sensor_control.h"
#include "water_control.h"

class MockEnvironment: public QObject {
    Q_OBJECT

    std::shared_ptr<Greenhouse> greenhouse_;
    SensorControl* sensor_control_;
    WaterControl* water_control_;

    float getRandomChange(const float min_change = -0.5, const float max_change = 0.5);
public:
    explicit MockEnvironment(std::shared_ptr<Greenhouse> greenhouse, SensorControl* sensor_control, WaterControl* water_control)
        : QObject(nullptr), greenhouse_(greenhouse), sensor_control_(sensor_control), water_control_(water_control) {}

public slots:
    void generateNewTemperature();
    void generateNewHumidity();
    void generateNewSoilMoistureAndFlow();
};

#endif // MOCK_ENVIROMENT_H
