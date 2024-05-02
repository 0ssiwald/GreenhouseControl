#include "log.h"
#include "date_time.h"
#include <memory>
#include <fstream>
#include <QtDebug>


void SystemLog::saveMessageToLog(const std::string& text, const std::chrono::system_clock::time_point timeStamp) {
    // Add message to vector
    std::shared_ptr<LogMessage> log_message = std::make_shared<LogMessage>(text, timeStamp);
    log_messages_.push_back(log_message);

    // Convert timeStamp to a string
    std::string timeStr = DateTimeConverter::timePointToString(timeStamp);
    // Open log file
    std::ofstream logfile(log_file_name_, std::ios::app);
    if (logfile.is_open()) {
        // Write to log file
        logfile << timeStr << ", " << text << std::endl;
        logfile.close();
    } else {
        throw std::runtime_error("Unable to open log file for saving messages.");
    }
}

void SystemLog::loadLogMessagesFromFile() {
    // Clear the current log messages
    log_messages_.clear();

    // Try to open the log file for reading
    std::ifstream logfile(log_file_name_);

    if (!logfile.is_open()) {
        // If the file doesn't exist, create it by opening it in write mode
        std::ofstream newFile(log_file_name_);
        if (!newFile.is_open()) {
            throw std::runtime_error("Unable to create log file.");
        }
        // Once the file is created, close it
        newFile.close();
        // Reopen the file for reading
        logfile.open(log_file_name_);
        if (!logfile.is_open()) {
            throw std::runtime_error("Unable to open log file for reading.");
        }
    }

    std::string line;
    // Read each line from the log file
    while (std::getline(logfile, line)) {
        // Use a stringstream to parse the line
        std::stringstream ss(line);

        // Parse the timestamp and message text
        std::string timeStr, messageText;
        if (std::getline(ss, timeStr, ',') && std::getline(ss, messageText)) {
            // Trim whitespace from the beginning and end of messageText
            messageText = messageText.substr(messageText.find_first_not_of(" "), messageText.find_last_not_of(" ") + 1);

            // Convert the timestamp string back to a time_point
            std::chrono::system_clock::time_point timeStamp = DateTimeConverter::stringToTimePoint(timeStr);

            // Create a LogMessage object and add it to the log_messages_ vector
            std::shared_ptr<LogMessage> logMessage = std::make_shared<LogMessage>(messageText, timeStamp);
            log_messages_.push_back(logMessage);
        }
    }

    // Close the log file
    logfile.close();
}
