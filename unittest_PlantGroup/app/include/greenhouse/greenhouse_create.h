#ifndef GREENHOUSE_CREATE_H
#define GREENHOUSE_CREATE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include "greenhouse.h"

// Class to create Greenhouse form File
// All the memory from the greenhouse is not deleted because
// it gets deleted when the programm shuts down (should be added later)
class GreenhouseCreate {
    Greenhouse* greenhouse_;
public:
    Greenhouse* loadGreenhouseFromFile(const std::string& file_name);
    // for testing when there are problems with the json
    Greenhouse* createGreenhouseFromCode();
};


#endif // GREENHOUSE_CREATE_H
