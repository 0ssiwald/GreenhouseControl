#include "greenhouse/greenhouse_create.h"
#include "date_time.h"


Greenhouse* GreenhouseCreate::createGreenhouseFromCode() {

    Fertilizer* fertilizer_1 = new Fertilizer("Biobizz Bloom", "Organic");
    Fertilizer* fertilizer_2 = new Fertilizer("Biobizz Grow", "Organic");
    Fertilizer* fertilizer_3 = new Fertilizer("Biobizz TopMax", "Organic");

    Condition* condition_week_1 = new Condition(70, 24, 40);
    condition_week_1->addFertilizer(fertilizer_1, 1);
    Condition* condition_week_2 = new Condition(65, 22, 40);
    condition_week_2->addFertilizer(fertilizer_1, 2);
    condition_week_2->addFertilizer(fertilizer_2, 1);
    Condition* condition_week_3 = new Condition(60, 20, 40);
    condition_week_3->addFertilizer(fertilizer_2, 3);
    condition_week_3->addFertilizer(fertilizer_3, 5);

    PlantProfile* plant_profile_1 = new PlantProfile("Purple Haze", 3, 8, 22.0, 3.0, "Coco", 70, 75);
    plant_profile_1->addWeeklyCondition(condition_week_1);
    plant_profile_1->addWeeklyCondition(condition_week_2);
    plant_profile_1->addWeeklyCondition(condition_week_3);
    PlantProfile* plant_profile_2 = new PlantProfile("Auto Sour Diesel", 3, 7, 23.0, 5.0, "Soil", 30, 90);
    plant_profile_2->addWeeklyCondition(condition_week_1);
    plant_profile_2->addWeeklyCondition(condition_week_2);
    plant_profile_2->addWeeklyCondition(condition_week_3);

    Plant* plant_1 = new Plant("1", DateTimeConverter::stringToTimePoint("20.05.2024 12:34:56"), plant_profile_1);
    SoilMoistureSensor* sensor1 = new SoilMoistureSensor;
    WaterValve* valve1 = new WaterValve;
    plant_1->setSoilSensor(sensor1);
    plant_1->setWaterValve(valve1);
    Plant* plant_2 = new Plant("2", DateTimeConverter::stringToTimePoint("20.05.2024 13:34:56"), plant_profile_1);
    SoilMoistureSensor* sensor2 = new SoilMoistureSensor;
    WaterValve* valve2 = new WaterValve;
    plant_2->setSoilSensor(sensor2);
    plant_2->setWaterValve(valve2);
    Plant* plant_3 = new Plant("3", DateTimeConverter::stringToTimePoint("10.05.2024 14:34:56"), plant_profile_2);
    SoilMoistureSensor* sensor3 = new SoilMoistureSensor;
    WaterValve* valve3 = new WaterValve;
    plant_3->setSoilSensor(sensor3);
    plant_3->setWaterValve(valve3);
    Plant* plant_4 = new Plant("4", DateTimeConverter::stringToTimePoint("10.05.2024 15:34:56"), plant_profile_2);
    SoilMoistureSensor* sensor4 = new SoilMoistureSensor;
    WaterValve* valve4 = new WaterValve;
    plant_4->setSoilSensor(sensor4);
    plant_4->setWaterValve(valve4);

    Note* note1 = new Note(DateTimeConverter::stringToTimePoint("21.04.2024 13:35:56"), "Test test 1");
    Note* note2 = new Note(DateTimeConverter::stringToTimePoint("22.04.2024 15:35:56"), "Test test 2");
    Note* note3 = new Note(DateTimeConverter::stringToTimePoint("23.04.2024 14:35:56"), "Test test 3");
    Note* note4 = new Note(DateTimeConverter::stringToTimePoint("24.04.2024 16:35:56"), "Test test 4");

    PlantGroup* plant_group_1 = new PlantGroup("1", 2, 1);
    plant_group_1->addPlantToGrid(plant_1, 0, 0);
    plant_group_1->addPlantToGrid(plant_2, 2, 1);
    plant_group_1->addNote(note1);
    plant_group_1->addNote(note2);
    PlantGroup* plant_group_2 = new PlantGroup("2", 0, 1);
    plant_group_2->addPlantToGrid(plant_3, 0, 0);
    plant_group_2->addPlantToGrid(plant_4, 0, 1);
    plant_group_2->addNote(note3);
    plant_group_2->addNote(note4);

    greenhouse_ = new Greenhouse(1,1);
    greenhouse_->addPlantGroupToGrid(plant_group_1, 0, 0);
    greenhouse_->addPlantGroupToGrid(plant_group_2, 1, 1);

    return greenhouse_;
}
