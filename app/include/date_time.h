#ifndef DATE_TIME_H
#define DATE_TIME_H

// Use QDateTime instead!!!!!!!!!!

/*
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

// for easy conversion of strings to time_points
struct DateTimeConverter {
    static std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeStr, const std::string& format = "%d.%m.%Y %H:%M:%S") {
        std::tm tm = {};
        std::istringstream ss(dateTimeStr);
        ss >> std::get_time(&tm, format.c_str());
        if (ss.fail()) {
            throw std::invalid_argument("Invalid date/time string: " + dateTimeStr);
        }

        // Adjust for the time zone offset
        std::time_t time_val = std::mktime(&tm);
        std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(time_val);

        return timePoint;
    }

    static std::string timePointToString(const std::chrono::system_clock::time_point& timePoint, const std::string& format = "%d.%m.%Y %H:%M:%S") {
        std::time_t time_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm* tm = std::localtime(&time_val);
        char buffer[64];
        std::strftime(buffer, sizeof(buffer), format.c_str(), tm);
        return std::string(buffer);
    }
};

*/
#endif // DATE_TIME_H
