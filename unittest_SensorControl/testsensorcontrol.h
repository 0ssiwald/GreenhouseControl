#include <QtTest>
#include <string>
#include "sensors_actors/sensor_control.h"
#include "greenhouse/plant.h"

class MockSensor: public Sensor {
public:

    float test_measurement_value_ = NAN; // why not a number

    MockSensor() = default;              // always default constructor for mock?????
    virtual ~MockSensor() = default;
    virtual float getMeasurement() override {return test_measurement_value_;}; // how to override ???
    virtual void setMeasurent(float measurement_value) override {test_measurement_value_ = measurement_value;}
};

class MockPlant: public Plant {
public:
    std::string test_plant_name_ = "TestName";

    MockPlant() = default;
    virtual ~MockPlant() = default;
    virtual std::string getPlantName() {return test_plant_name_;}
};


class TestSensorControl : public QObject {
    Q_OBJECT

    SensorControl *sut;

    std::shared_ptr<MockSensor> mock_temperature_sensor_;
    std::shared_ptr<MockSensor> mock_humidity_sensor_;
    std::map<std::shared_ptr<MockPlant>, std::shared_ptr<MockSensor>> mock_plants_with_soil_moisture_sensors_;

public:
    explicit TestSensorControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testAddSoilSensors(); // Needs testing???????????
    void testMeasureTemperature();
    void testMeasureHumidity();
    void testMeasureSoilMoistures();
};
