#include "greenhouse/greenhouse.h"
#include <QDateTime>
//#include "date_time.h"

void Greenhouse::addPlantGroupToGrid(std::shared_ptr<PlantGroup> pg, int row_position, int column_position) {
    // Check viability of row and column numbers
    if (row_position > number_of_group_rows_ || column_position > number_of_group_columns_) {
        qDebug() << "row problem";
        throw("Plant Group cant be added"); // Throw needs catch?????????????????????
        return;
    }
    for(auto &it: plant_groups_) {
        if(it->getGridRowNumber() == row_position && it->getGridColumnNumber() == column_position) {
            qDebug() << "column problem";
            throw("Plant Group cant be added"); // Throw needs catch?????????????????????
            return;
        }
    }
    pg->setGridPosition(row_position, column_position);
    plant_groups_.push_back(pg);
    return;
}

void Greenhouse::setGroupGridSize(int row_size, int column_size) {
    number_of_group_rows_ = row_size;
    number_of_group_columns_ = column_size;
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

    std::shared_ptr<PlantProfile> plant_profile_1 = std::shared_ptr<PlantProfile>(new PlantProfile("Purple Haze", 3, 8, 22.0, 3.0, "Coco", 10,  20));
    plant_profile_1->addWeeklyCondition(condition_week_1);
    plant_profile_1->addWeeklyCondition(condition_week_2);
    plant_profile_1->addWeeklyCondition(condition_week_3);

    std::shared_ptr<PlantProfile> plant_profile_2 = std::shared_ptr<PlantProfile>(new PlantProfile("Auto Sour Diesel", 3, 7, 23.0, 5.0, "Soil", 10,  20));
    plant_profile_2->addWeeklyCondition(condition_week_1);
    plant_profile_2->addWeeklyCondition(condition_week_2);
    plant_profile_2->addWeeklyCondition(condition_week_3);

    // The format of the date and time string
    QString format = "dd.MM.yyyy HH:mm:ss";
    std::shared_ptr<Plant> plant_1 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("21.04.2023 12:34:56", format), plant_profile_1));
    std::shared_ptr<Plant> plant_2 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("22.04.2023 13:34:56", format), plant_profile_1));
    std::shared_ptr<Plant> plant_3 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("23.04.2023 14:34:56", format), plant_profile_2));
    std::shared_ptr<Plant> plant_4 = std::shared_ptr<Plant>(new Plant(QDateTime::fromString("24.04.2023 15:34:56", format), plant_profile_2));


    std::shared_ptr<PlantGroup> plant_group_1 = std::make_shared<PlantGroup>(2, 1);
    plant_group_1->addPlantToGrid(plant_1, 0, 0);
    plant_group_1->addPlantToGrid(plant_2, 2, 1);
    std::shared_ptr<PlantGroup> plant_group_2 = std::make_shared<PlantGroup>(0, 1);
    plant_group_2->addPlantToGrid(plant_3, 0, 0);
    plant_group_2->addPlantToGrid(plant_4, 0, 1);

    greenhouse = std::make_shared<Greenhouse>(1,2);
    greenhouse->addPlantGroupToGrid(plant_group_1, 0, 0);
    greenhouse->addPlantGroupToGrid(plant_group_2, 1, 2);

    return greenhouse;
}


QDebug operator<<(QDebug qdebug, const Greenhouse &gh) {
    qdebug << "Greenhouse: " << Qt::endl;
    qdebug << "size_of_group_gird_rows: " << gh.number_of_group_rows_ << Qt::endl;
    qdebug << "size_of_group_gird_columns: " << gh.number_of_group_columns_ << Qt::endl;
    qdebug << "there are " << gh.plant_groups_.size() << " plant_groups" << Qt::endl << Qt::endl;
    int i = 1;
    for(auto& it: gh.plant_groups_) {
        qdebug << "Plant Group " << i << Qt::endl;
        qdebug << *it << Qt::endl;
        i++;
    }
    return qdebug;
}
