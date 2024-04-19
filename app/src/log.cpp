#include "log.h"

/*
void SystemLog::saveMessageToLog(std::string text, std::chrono::system_clock::time_point timeStamp) {
    // Convert timeStamp to a string
    std::time_t time = std::chrono::system_clock::to_time_t(timeStamp);
    std::string timeStr = std::ctime(&time); // Convert to human-readable string

    // Open log file
    std::ofstream logfile(log_file_name, std::ios::app);
    if (logfile.is_open()) {
        // Write to log file
        logfile << timeStr << " : " << text << std::endl;
        logfile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}
*/
