#include "greenhouse/greenhouse.h"
#include <QDateTime>
//#include "date_time.h"

void Greenhouse::addPlantGroup(std::shared_ptr<PlantGroup> pg) {
    // Temporary way to add plant groups just to rows
    number_of_group_columns = 1;
    number_of_group_rows += 1;

    plant_groups.push_back(pg);
    return;
}

std::shared_ptr<Greenhouse> GreenhouseCreate::createGreenhouseFromCode() {

    std::shared_ptr<Fertilizer> fertilizer_1 = std::shared_ptr<Fertilizer>(new Fertilizer("Biobizz Bloom", "Organic"));
    std::shared_ptr<Fertilizer> fertilizer_2 = std::shared_ptr<Fertilizer>(new Fertilizer("Biobizz Grow", "Organic"));
    std::shared_ptr<Fertilizer> fertilizer_3 = std::shared_ptr<Fertilizer>(new Fertilizer("Biobizz TopMax", "Organic"));

    std::shared_ptr<Condition> condition_week_1 = std::shared_ptr<Condition>(new Condition(1, 70, 24, 40));
    condition_week_1->addFertilizer(fertilizer_1, 1);
    std::shared_ptr<Condition> condition_week_2 = std::shared_ptr<Condition>(new Condition(2, 65, 22, 40));
    condition_week_2->addFertilizer(fertilizer_1, 2);
    condition_week_2->addFertilizer(fertilizer_2, 1);
    std::shared_ptr<Condition> condition_week_3 = std::shared_ptr<Condition>(new Condition(3, 60, 20, 40));
    condition_week_3->addFertilizer(fertilizer_2, 3);
    condition_week_3->addFertilizer(fertilizer_3, 5);

    std::shared_ptr<PlantProfile> plant_profile_1 = std::shared_ptr<PlantProfile>(new PlantProfile("Purple Haze", 3, 8, 3.0, 22.0, "Coco", 10,  20));
    plant_profile_1->addWeeklyCondition(condition_week_1);
    plant_profile_1->addWeeklyCondition(condition_week_2);
    plant_profile_1->addWeeklyCondition(condition_week_3);

    std::shared_ptr<PlantProfile> plant_profile_2 = std::shared_ptr<PlantProfile>(new PlantProfile("Auto Sour Diesel", 3, 7, 2.0, 18.0, "Soil", 10,  20));
    plant_profile_2->addWeeklyCondition(condition_week_1);
    plant_profile_2->addWeeklyCondition(condition_week_2);
    plant_profile_2->addWeeklyCondition(condition_week_3);

    // The format of the date and time string
    QString format = "dd.MM.yyyy HH:mm:ss";
    std::shared_ptr<Plant> plant_1 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("21.04.2023 12:34:56", format), plant_profile_1));
    std::shared_ptr<Plant> plant_2 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("22.04.2023 13:34:56", format), plant_profile_1));
    std::shared_ptr<Plant> plant_3 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("23.04.2023 14:34:56", format), plant_profile_2));
    std::shared_ptr<Plant> plant_4 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("24.04.2023 15:34:56", format), plant_profile_2));


    std::shared_ptr<PlantGroup> plant_group_1 = std::shared_ptr<PlantGroup>(new PlantGroup());
    plant_group_1->addPlant(plant_1);
    plant_group_1->addPlant(plant_2);
    std::shared_ptr<PlantGroup> plant_group_2 = std::shared_ptr<PlantGroup>(new PlantGroup());
    plant_group_2->addPlant(plant_3);
    plant_group_2->addPlant(plant_4);

    greenhouse = std::shared_ptr<Greenhouse>(new Greenhouse());
    greenhouse->addPlantGroup(plant_group_1);
    greenhouse->addPlantGroup(plant_group_2);

    return greenhouse;
}


QDebug operator<<(QDebug qdebug, const Greenhouse &gh) {
    qdebug << "Greenhouse: " << Qt::endl;
    qdebug << "number_of_group_rows: " << gh.number_of_group_rows << Qt::endl;
    qdebug << "number_of_group_columns: " << gh.number_of_group_columns << Qt::endl;
    qdebug << "there are " << gh.plant_groups.size() << " plant_groups" << Qt::endl << Qt::endl;
    int i = 1;
    for(auto& it: gh.plant_groups) {
        qdebug << "Plant Group " << i << Qt::endl;
        qdebug << *it << Qt::endl;
        i++;
    }
    return qdebug;
}
