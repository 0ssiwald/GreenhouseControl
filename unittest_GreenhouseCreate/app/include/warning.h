#ifndef WARNING_H
#define WARNING_H

#include <string>

// interface
class SendWarning {
public:
    virtual bool sendEmail(const std::string&) = 0;
};

//implementation needed

class Warning {
    std::string warning_text;
    SendWarning* send_warning;
public:
    bool sendWarning();
};

class FireAlarm {
    SendWarning* send_waring;
public:
    bool sendAlarm();
    void shutOffAlarm();
};

#endif // WARNING_H
