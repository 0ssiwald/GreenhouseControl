#ifndef LOG_H
#define LOG_H

#include <string>
#include <chrono>
#include <vector>
#include <memory>


struct LogMessage {
    std::string message_text_;
    std::chrono::system_clock::time_point time_point_;
    LogMessage(const std::string& message_text, std::chrono::system_clock::time_point time_point)
        : message_text_(message_text), time_point_(time_point) {}
};


class SystemLog {
    std::string log_file_name_;
    std::vector<std::shared_ptr<LogMessage>> log_messages_;
public:
    SystemLog(const std::string& log_file_name)
        : log_file_name_(log_file_name) {}
    void displayLog();
    void loadLogMessagesFromFile();
    std::vector<std::shared_ptr<LogMessage>> getLogMessages() {return log_messages_;};
    void saveMessageToLog(const std::string&, const std::chrono::system_clock::time_point);

};






#endif // LOG_H
