#ifndef MOCK_ENVIRONMENT_H
#define MOCK_ENVIRONMENT_H

#include <QObject>
#include "sensor_control.h"
#include "water_control.h"

class MockEnvironment: public QObject {
    Q_OBJECT
    SensorControl* sensor_control_;
    WaterControl* water_control_;
    float flow_value_;

public:
    explicit MockEnvironment( SensorControl* sensor_control, WaterControl* water_control)
        : QObject(nullptr), sensor_control_(sensor_control), water_control_(water_control) {}
    float getRandomChange(const float min_change = -0.5, const float max_change = 0.5);
public slots:
    void generateNewTemperature();
    void generateNewHumidity();
    void generateNewSoilMoisture(Plant*);
    void generateNewFlow(WaterValve*);
};

#endif // MOCK_ENVIRONMENT_H
