#ifndef MOCK_ENVIROMENT_H
#define MOCK_ENVIROMENT_H

#include <QObject>
#include "sensor_control.h"
#include "water_control.h"

class MockEnvironment: public QObject {
    Q_OBJECT
    SensorControl* sensor_control_;
    WaterControl* water_control_;
    float flow_value_;

    float getRandomChange(const float min_change = -0.5, const float max_change = 0.5);
public:
    explicit MockEnvironment( SensorControl* sensor_control, WaterControl* water_control)
        : QObject(nullptr), sensor_control_(sensor_control), water_control_(water_control) {}

public slots:
    void generateNewTemperature();
    void generateNewHumidity();
    void generateNewSoilMoisture(Plant*);
    void generateNewFlow(WaterValve*);
};

#endif // MOCK_ENVIROMENT_H
