#include "testgreenhousecontrol.h"


void TestGreenhousecontrol::initTestCase() {
    Q_INIT_RESOURCE(data);
}

void TestGreenhousecontrol::cleanupTestCase() {}

void TestGreenhousecontrol::testGreenhousecontrol() {
    GreenhouseCreate ghc;
    Greenhouse* greenhouse = ghc.loadGreenhouseFromFile(":/greenhouse_systemtest.json");
    TemperatureSensor temperature_sensor(7.0);
    HumiditySensor humidity_sensor(5.0);
    SensorControl sensorControl(&temperature_sensor, &humidity_sensor, greenhouse);
    WaterValve main_valve(true);
    FlowSensor flow_sensor(0.0);
    WaterControl waterControl(&main_valve, &flow_sensor, greenhouse);

    // measure all sensors
    QSignalSpy spy = QSignalSpy(&sensorControl, SIGNAL(temperatureMeasured(float)));
    sensorControl.measureTemperature();
    QVERIFY(spy.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy.takeLast().at(0).toFloat(), 7.0f)); // test for the right emmited value

    QSignalSpy spy2 = QSignalSpy(&sensorControl, SIGNAL(humidityMeasured(float)));
    sensorControl.measureHumidity();
    QVERIFY(spy2.count() == 1);    // one signal emitted
    QVERIFY(qFuzzyCompare(spy2.takeLast().at(0).toFloat(), 5.0f)); // test for the right emmited value

    QSignalSpy spy3 = QSignalSpy(&sensorControl, SIGNAL(updateSoilMoisture(Plant*)));
    sensorControl.measureSoilMoistures();
    QVERIFY(spy3.count() == 2); // two plants should be measured

    // Test if watering works
    QVERIFY(greenhouse->getPlantGroups()[0]->getPlants()[0]->getWaterValve()->getValveIsOpen() == false);
    QVERIFY(greenhouse->getPlantGroups()[0]->getPlants()[1]->getWaterValve()->getValveIsOpen() == false);
    waterControl.controlMoistureLevels();
    QVERIFY(greenhouse->getPlantGroups()[0]->getPlants()[0]->getWaterValve()->getValveIsOpen() == true); // first plant should be watered
    QVERIFY(greenhouse->getPlantGroups()[0]->getPlants()[1]->getWaterValve()->getValveIsOpen() == false); // secound not because of threshold
}


QTEST_APPLESS_MAIN(TestGreenhousecontrol)
