#include "test_sensor_sensorcontrol.h"

std::vector<Plant*> mock_plants;

std::vector<Plant*> Greenhouse::getAllPlants() {
    return mock_plants;
}

void TestSensorSenorControl::initTestCase() {
    temperatureSensor = new TemperatureSensor(0.0);
    humiditySensor = new HumiditySensor(0.0);
    soilSensor1 = new SoilMoistureSensor(0.0);
    soilSensor2 = new SoilMoistureSensor(0.0);
    mock_greenhouse = new Greenhouse;
    sensorControl = new SensorControl(temperatureSensor, humiditySensor, mock_greenhouse);
}

void TestSensorSenorControl::cleanupTestCase() {
    delete temperatureSensor;
    delete humiditySensor;
    delete sensorControl;
    delete mock_greenhouse;
}

void TestSensorSenorControl::TestMeasureTemperature() {
    QSignalSpy spy = QSignalSpy(sensorControl, SIGNAL(temperatureMeasured(float)));
    temperatureSensor->setMeasurent(5.0);
    QVERIFY(temperatureSensor->getMeasurement() == 5.0);
    sensorControl->measureTemperature();
    QVERIFY(spy.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy.takeLast().at(0).toFloat(), 5.0f)); // test for the right emmited value
}
void TestSensorSenorControl::TestMeasureHumidity() {
    QSignalSpy spy = QSignalSpy(sensorControl, SIGNAL(humidityMeasured(float)));
    humiditySensor->setMeasurent(7.0);
    QVERIFY(humiditySensor->getMeasurement() == 7.0);
    sensorControl->measureHumidity();
    QVERIFY(spy.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy.takeLast().at(0).toFloat(), 7.0f)); // test for the right emmited value
}
void TestSensorSenorControl::TestMeasureSoilMoistures() {
    QSignalSpy spy1 = QSignalSpy(sensorControl, SIGNAL(updateSoilMoisture(Plant*)));
    QSignalSpy spy2 = QSignalSpy(sensorControl, SIGNAL(soilMoisturesMeasured()));
    // Test without plants
    sensorControl->measureSoilMoistures();
    QVERIFY(spy1.count() == 0); // because 0 plants should be measured (mock_plants is empty)
    QVERIFY(spy2.count() == 1);
    // Now test with 2 plants and two sensors
    Plant *plant1 = new Plant();
    Plant *plant2 = new Plant();
    plant1->setSoilSensor(soilSensor1);
    plant2->setSoilSensor(soilSensor2);
    mock_plants.push_back(plant1);
    mock_plants.push_back(plant2);
    sensorControl->measureSoilMoistures();
    QVERIFY(spy1.count() == 2); // because 2 plants should be measured
    QVERIFY(spy2.count() == 2); // now 2 because measureSoilMoistures() was called 2 times
    delete plant1;
    delete plant2;
}


QTEST_APPLESS_MAIN(TestSensorSenorControl)
