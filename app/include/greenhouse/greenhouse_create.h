#ifndef GREENHOUSE_CREATE_H
#define GREENHOUSE_CREATE_H

#include "greenhouse.h"

// Class to create Greenhouse form File
// At the moment just created in code
class GreenhouseCreate {
    Greenhouse* greenhouse_;
public:
    Greenhouse* createGreenhouseFromCode();
    // for later
    Greenhouse loadGreenhouseFromFile(const std::string&);
};


#endif // GREENHOUSE_CREATE_H
