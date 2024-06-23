#include "testsensorcontrol.h"

int number_of_measurements = 0;
float sensor_value = 5.0;
std::vector<Plant*> mock_plants;

float Sensor::getMeasurement() {
    number_of_measurements += 1;
    return sensor_value;
}

std::vector<Plant*> Greenhouse::getAllPlants() {
    return mock_plants;
}

void TestSensorControl::init() {
    number_of_measurements = 0;
}

void TestSensorControl::cleanup() {}

void TestSensorControl::initTestCase() {
    mock_plant1_ = new MockPlant;
    mock_plants.push_back(mock_plant1_);
    mock_plant2_ = new MockPlant;
    mock_plants.push_back(mock_plant2_);
    mock_temperature_sensor_ = new Sensor(0);
    mock_humidity_sensor_ = new Sensor(0);
    mock_greenhouse_ = new Greenhouse();

    sut = new SensorControl(mock_temperature_sensor_, mock_humidity_sensor_, mock_greenhouse_);
}

void TestSensorControl::cleanupTestCase() {
    delete sut;
    sut = nullptr;
    delete mock_plant1_;
    delete mock_plant2_;
    delete mock_temperature_sensor_;
    delete mock_humidity_sensor_;
    delete mock_greenhouse_;
}


void TestSensorControl::testMeasureTemperature() {
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(temperatureMeasured(float)));
    QVERIFY(number_of_measurements == 0);
    sut->measureTemperature();
    QVERIFY(number_of_measurements == 1); // one measurement should happen
    QVERIFY(spy.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy.takeLast().at(0).toFloat(), 5.0f)); // test for the right emmited value
}
void TestSensorControl::testMeasureHumidity() {
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(humidityMeasured(float)));
    QVERIFY(number_of_measurements == 0);
    sut->measureHumidity();
    QVERIFY(number_of_measurements == 1); // one measurement should happen
    QVERIFY(spy.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy.takeLast().at(0).toFloat(), 5.0f)); // test for the right emmited value
}
void TestSensorControl::testMeasureSoilMoistures() {
    QSignalSpy spy1 = QSignalSpy(sut, SIGNAL(updateSoilMoisture(Plant*)));
    QSignalSpy spy2 = QSignalSpy(sut, SIGNAL(soilMoisturesMeasured()));
    QVERIFY(number_of_measurements == 0);
    sut->measureSoilMoistures();
    QVERIFY(number_of_measurements == 2); // because 2 plants should be measured
    QVERIFY(spy1.count() == 2); // because 2 plants should be measured
    QVERIFY(spy2.count() == 1);
}
QTEST_APPLESS_MAIN(TestSensorControl);

