#include "greenhouse/greenhouse_create.h"
#include "date_time.h"

Greenhouse* GreenhouseCreate::loadGreenhouseFromFile(const std::string& file_name) {
    QFile file(QString::fromStdString(file_name));
    // Test if the file was found
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open file.");
        return nullptr;
    }

    QByteArray fileData = file.readAll();
    file.close();
    // Test if the read document is in a valid format
    QJsonDocument doc(QJsonDocument::fromJson(fileData));
    if (doc.isNull() || !doc.isObject()) {
        qWarning("Invalid JSON document.");
        return nullptr;
    }

    QJsonObject jsonObj = doc.object();

    unsigned int greenhouseRows = jsonObj["number_of_group_rows"].toInt();
    unsigned int greenhouseCols = jsonObj["number_of_group_columns"].toInt();
    greenhouse_ = new Greenhouse(greenhouseRows, greenhouseCols);

    QJsonArray plantGroupsArray = jsonObj["plant_groups"].toArray();
    for (const QJsonValue& groupValue : plantGroupsArray) {
        QJsonObject groupObj = groupValue.toObject();
        QString groupName = groupObj["group_name"].toString();
        unsigned int groupRows = groupObj["number_of_plant_rows"].toInt();
        unsigned int groupCols = groupObj["number_of_plant_columns"].toInt();
        PlantGroup* plantGroup = new PlantGroup(groupName.toStdString(), groupRows, groupCols);

        QJsonArray plantsArray = groupObj["plants"].toArray();
        for (const QJsonValue& plantValue : plantsArray) {
            QJsonObject plantObj = plantValue.toObject();
            QString plantName = plantObj["plant_name"].toString();
            std::chrono::system_clock::time_point sowingDate = DateTimeConverter::stringToTimePoint(plantObj["sowing_date"].toString().toStdString());
            unsigned int plantRow = plantObj["plant_grid_row_number"].toInt();
            unsigned int plantCol = plantObj["plant_grid_column_number"].toInt();

            QJsonObject profileObj = plantObj["profile"].toObject();
            PlantProfileAttributes profileAtributes;
            profileAtributes.strain_name_ = profileObj["strain_name"].toString().toStdString();
            profileAtributes.length_vegitation_period_ = profileObj["length_vegitation_period"].toInt();
            profileAtributes.length_flowering_period_ = profileObj["length_flowering_period"].toInt();
            profileAtributes.expected_thc_content_ = profileObj["expected_thc_content"].toDouble();
            profileAtributes.expected_cbd_content_ = profileObj["expected_cbd_content"].toDouble();
            profileAtributes.soil_type_ = profileObj["soil_type"].toString().toStdString();
            profileAtributes.lower_watering_threshold_ = profileObj["lower_watering_threshold"].toInt();
            profileAtributes.upper_watering_threshold_ = profileObj["upper_watering_threshold"].toInt();

            PlantProfile* profile = new PlantProfile(profileAtributes);

            QJsonArray conditionsArray = profileObj["weekly_conditions"].toArray();
            std::vector<Condition*> conditions;
            for (const QJsonValue& conditionValue : conditionsArray) {
                QJsonObject conditionObj = conditionValue.toObject();
                float humidity = conditionObj["humidity"].toDouble();
                float temperature = conditionObj["temperature"].toDouble();
                int lampDistance = conditionObj["lamp_distance"].toInt();
                Condition* condition = new Condition(humidity, temperature, lampDistance);

                QJsonArray fertilizersArray = conditionObj["fertilizers"].toArray();
                for (const QJsonValue& fertilizerValue : fertilizersArray) {
                    QJsonObject fertilizerObj = fertilizerValue.toObject();
                    QString fertilizerName = fertilizerObj["name"].toString();
                    QString fertilizerType = fertilizerObj["type"].toString();
                    int amount = fertilizerObj["amount"].toInt();
                    Fertilizer* fertilizer = new Fertilizer(fertilizerName.toStdString(), fertilizerType.toStdString());
                    condition->addFertilizer(fertilizer, amount);
                }
                conditions.push_back(condition);
            }
            profile->setWeeklyConditions(conditions);

            Plant* plant = new Plant(plantName.toStdString(), sowingDate, profile, plantRow, plantCol);
            plantGroup->addPlantToGrid(plant, plantRow, plantCol);
            // Every created plant gets a valve and a soil sensor
            SoilMoistureSensor* sensor = new SoilMoistureSensor;
            WaterValve* valve = new WaterValve;
            plant->setSoilSensor(sensor);
            plant->setWaterValve(valve);
        }

        QJsonArray notesArray = groupObj["notes"].toArray();
        for (const QJsonValue& noteValue : notesArray) {
            QJsonObject noteObj = noteValue.toObject();
            std::chrono::system_clock::time_point creationDate = DateTimeConverter::stringToTimePoint(noteObj["creation_date"].toString().toStdString());
            QString message = noteObj["message"].toString();
            Note* note = new Note(creationDate, message.toStdString());
            plantGroup->addNote(note);
        }

        unsigned int groupRow = groupObj["grid_row"].toInt();
        unsigned int groupCol = groupObj["grid_column"].toInt();
        greenhouse_->addPlantGroupToGrid(plantGroup, groupRow, groupCol);
    }
    return greenhouse_;
}

// Alternitve for creating a greenhouse only used for testing
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
    std::vector<Condition*> conditions = {condition_week_1, condition_week_2, condition_week_3};

    PlantProfileAttributes profileAtributes;
    profileAtributes.strain_name_ = "Sour Diesel Auto";
    profileAtributes.length_vegitation_period_ = 3;
    profileAtributes.length_flowering_period_ = 8;
    profileAtributes.expected_thc_content_ = 22.0;
    profileAtributes.expected_cbd_content_ = 3.0;
    profileAtributes.soil_type_ = "Coco";
    profileAtributes.lower_watering_threshold_ = 70;
    profileAtributes.upper_watering_threshold_ = 75;

    PlantProfile* plant_profile_1 = new PlantProfile(profileAtributes);
    plant_profile_1->setWeeklyConditions(conditions);
    profileAtributes.strain_name_ = "Purple Haze";
    profileAtributes.length_vegitation_period_ = 3;
    profileAtributes.length_flowering_period_ = 9;
    profileAtributes.expected_thc_content_ = 20.0;
    profileAtributes.expected_cbd_content_ = 6.0;
    profileAtributes.soil_type_ = "Coco";
    profileAtributes.lower_watering_threshold_ = 35;
    profileAtributes.upper_watering_threshold_ = 50;
    PlantProfile* plant_profile_2 = new PlantProfile(profileAtributes);
    plant_profile_2->setWeeklyConditions(conditions);

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

    Note* note1 = new Note(DateTimeConverter::stringToTimePoint("21.04.2024 13:35:56"), "Pflanzen wurde gedüngt");
    Note* note2 = new Note(DateTimeConverter::stringToTimePoint("22.04.2024 15:35:56"), "Untere Blätter wurden entfehrnt");
    Note* note3 = new Note(DateTimeConverter::stringToTimePoint("23.04.2024 14:35:56"), "Pflanze 1 wurde mit LST trainiert");
    Note* note4 = new Note(DateTimeConverter::stringToTimePoint("24.04.2024 16:35:56"), "Pflanzen wurde gedüngt");

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
