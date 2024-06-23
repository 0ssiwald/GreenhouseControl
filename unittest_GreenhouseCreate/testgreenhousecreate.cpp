#include "testgreenhousecreate.h"
#include "date_time.h"

std::string testFileName = "test_greenhouse.json";
const float epsilon = 1.0e-4;   // fixed epsilon for comparison of float numbers

// All needed definitions from the source files
unsigned int Plant::getGridRowNumber() {return plant_grid_row_number_;}
unsigned int Plant::getGridColumnNumber() {return plant_grid_column_number_;}
unsigned int PlantGroup::getGridRowNumber() {return group_grid_row_number_;}
unsigned int PlantGroup::getGridColumnNumber() {return group_grid_column_number_;}
std::vector<Plant*> PlantGroup::getPlants() {return plants_;}
void Condition::addFertilizer(Fertilizer* fertilizer, int amount) {fertilizers_.emplace_back(fertilizer, amount);}
bool PlantGroup::addPlantToGrid(Plant* plant, unsigned int row_number,unsigned int column_number) {
    plant->setGridPosition(row_number, column_number);
    plants_.push_back(plant);
    return true;
}
void PlantGroup::addNote(Note* note) {notes_.push_back(note);}
bool Greenhouse::addPlantGroupToGrid(PlantGroup* pg, unsigned int row_position, unsigned int column_position) {
    pg->setGridPosition(row_position, column_position);
    plant_groups_.push_back(pg);
    return true;
}
void Plant::setGridPosition(unsigned int row_number,unsigned int column_number) {
    plant_grid_row_number_ = row_number;
    plant_grid_column_number_ = column_number;
}
void PlantGroup::setGridPosition(unsigned int row_number,unsigned int column_number) {
    group_grid_row_number_ = row_number;
    group_grid_column_number_ = column_number;
}

PlantProfile::PlantProfile(PlantProfileAttributes attributes) {
    expected_cbd_content_ = attributes.expected_cbd_content_;
    expected_thc_content_ = attributes.expected_thc_content_;
    length_flowering_period_ = attributes.length_flowering_period_;
    length_vegitation_period_ = attributes.length_vegitation_period_;
    lower_watering_threshold_ = attributes.lower_watering_threshold_;
    upper_watering_threshold_ = attributes.upper_watering_threshold_;
    soil_type_ = attributes.soil_type_;
    strain_name_ = attributes.strain_name_;
}

void TestGreenhouseCreate::init() {
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
                                    "strain_name": "Strain1",
                                    "length_vegitation_period": 5,
                                    "length_flowering_period": 7,
                                    "expected_thc_content": 15.5,
                                    "expected_cbd_content": 0.5,
                                    "soil_type": "Soil1",
                                    "lower_watering_threshold": 20,
                                    "upper_watering_threshold": 40,
                                    "weekly_conditions": [
                                        {
                                            "humidity": 50.0,
                                            "temperature": 22.0,
                                            "lamp_distance": 30,
                                            "fertilizers": [
                                                {
                                                    "name": "Fertilizer1",
                                                    "type": "Type1",
                                                    "amount": 10
                                                }
                                            ]
                                        }
                                    ]
                                }
                            }
                        ],
                        "notes": [
                            {
                                "creation_date": "21.05.2024 14:34:56",
                                "message": "Note1"
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


void TestGreenhouseCreate::cleanup() {
    // Clean up the mock JSON file
    QFile::remove(QString::fromStdString(testFileName));
}

void TestGreenhouseCreate::initTestCase() {
    sut = new GreenhouseCreate;
}

void TestGreenhouseCreate::cleanupTestCase() {
    delete sut;
}

void TestGreenhouseCreate::testLoadGreenhouseFromFile() {
    Greenhouse* greenhouse = sut->loadGreenhouseFromFile(testFileName);

    // Verify the greenhouse dimensions
    unsigned int i = 2;
    QCOMPARE(greenhouse->getNumberOfRows(), i);
    QCOMPARE(greenhouse->getNumberOfColumns(), i);

    // Verify the plant group details
    QVERIFY(greenhouse->getPlantGroups().size() == 1);
    PlantGroup* group = greenhouse->getPlantGroups()[0];
    QCOMPARE(group->getGroupName(), "Group1");
    QCOMPARE(group->getNumberOfPlantRows(), i);
    QCOMPARE(group->getNumberOfPlantColumns(), i);

    // Verify the plant details
    QVERIFY(group->getPlants().size() == 1);
    Plant* plant = group->getPlants()[0];

    QCOMPARE(plant->getPlantName(), "Plant1");
    QCOMPARE(plant->getSowingDate(), DateTimeConverter::stringToTimePoint("20.05.2024 13:34:56"));

    PlantProfile* profile = plant->getPlantProfile();
    QCOMPARE(profile->getStrainName(), "Strain1");
    QCOMPARE(profile->getLengthVegitationPeriod(), 5);
    QCOMPARE(profile->getLengthFloweringPeriod(), 7);
    QVERIFY(profile->getExpectedThcContent() - 15.5 <= epsilon);   // fixed epsilon for comparison of float numbers);
    QVERIFY(profile->getExpectedCbdContent() - 0.5 <= epsilon);
    QCOMPARE(profile->getSoilType(), "Soil1");
    QCOMPARE(profile->getLowerWateringThreshold(), 20);
    QCOMPARE(profile->getUpperWateringThreshold(), 40);

    // Verify the weekly conditions
    QVERIFY(profile->getConditionsWeekly().size() == 1);
    Condition* condition = profile->getConditionsWeekly()[0];
    QVERIFY(condition->getHumidity() - 50.0 <= epsilon);
    QVERIFY(condition->getTemperature() - 22.0<= epsilon);
    QCOMPARE(condition->getLampDistance(), 30);

    // Verify the fertilizers
    QVERIFY(condition->getFertilizers().size() == 1);
    FertilizerWithAmount fertilizer = condition->getFertilizers()[0];
    QCOMPARE(fertilizer.getFertilizer()->getName(), "Fertilizer1");
    QCOMPARE(fertilizer.getAmount(), 10);

    // Verify the notes
    QVERIFY(group->getNotes().size() == 1);
    Note* note = group->getNotes()[0];
    QVERIFY(note !=  nullptr);
    QCOMPARE(note->getDate(), DateTimeConverter::stringToTimePoint("21.05.2024 14:34:56"));
    QCOMPARE(note->getMessage(), "Note1");

    // cleanup
    delete greenhouse;
    delete group;
    delete plant;
    delete profile;
    delete note;
}

QTEST_APPLESS_MAIN(TestGreenhouseCreate)
