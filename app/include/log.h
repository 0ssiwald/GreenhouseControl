#ifndef LOG_H
#define LOG_H

#include <string>
#include <chrono>

class SystemLog {
    std::string log_file_name;
public:
    SystemLog(const std::string& log_file_name = "log.csv")
        : log_file_name(log_file_name) {}
    void displayLog();
    bool loadLogFromFile();
    void saveMessageToLog(const std::string& text, std::chrono::system_clock::time_point timeStamp);

};





#endif // LOG_H
