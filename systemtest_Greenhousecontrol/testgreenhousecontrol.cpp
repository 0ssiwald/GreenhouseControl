#include "testgreenhousecontrol.h"

std::string testFileName = "test_greenhouse.json";

void TestGreenhousecontrol::initTestCase() {
    // Create a mock JSON file for testing
    QFile file(QString::fromStdString(testFileName));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << R"({
                "number_of_group_rows": 2,
                "number_of_group_columns": 2,
                "plant_groups": [
                    {
                        "group_name": "Group1",
                        "number_of_plant_rows": 2,
                        "number_of_plant_columns": 2,
                        "plants": [
                            {
                                "plant_name": "Plant1",
                                "sowing_date": "20.05.2024 13:34:56",
                                "plant_grid_row_number": 0,
                                "plant_grid_column_number": 0,
                                "profile": {
                                    "lower_watering_threshold": 80,
                                    "upper_watering_threshold": 90,
                                    "weekly_conditions": [
                                    ]
                                }
                            },
                            {
                                "plant_name": "Plant2",
                                "sowing_date": "20.05.2024 13:34:56",
                                "plant_grid_row_number": 0,
                                "plant_grid_column_number": 1,
                                "profile": {
                                    "lower_watering_threshold": 60,
                                    "upper_watering_threshold": 90,
                                    "weekly_conditions": [
                                    ]
                                }
                            }
                        ],
                        "grid_row": 0,
                        "grid_column": 0
                    }
                ]
            })";
        file.close();
    }

}

void TestGreenhousecontrol::cleanupTestCase() {
    // Clean up the mock JSON file
    QFile::remove(QString::fromStdString(testFileName));
}

void TestGreenhousecontrol::testGreenhousecontrol() {
    GreenhouseCreate ghc;
    Greenhouse* greenhouse = ghc.loadGreenhouseFromFile(testFileName);
    TemperatureSensor temperature_sensor(7.0);
    HumiditySensor humidity_sensor(5.0);
    SensorControl sensorControl(&temperature_sensor, &humidity_sensor, greenhouse);
    WaterValve main_valve(true);
    FlowSensor flow_sensor(0.0);
    WaterControl waterControl(&main_valve, &flow_sensor, greenhouse);
    MockEnvironment mockEnvironment(&sensorControl, &waterControl);

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
