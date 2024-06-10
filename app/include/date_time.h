#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

// A few functions to make converting between strings and time_point easier
namespace DateTimeConverter {

     inline std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeStr, const std::string& format = "%d.%m.%Y %H:%M:%S") {
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

     inline std::string timePointToString(const std::chrono::system_clock::time_point& timePoint, const std::string& format = "%d.%m.%Y %H:%M:%S") {
        std::time_t time_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm* tm = std::localtime(&time_val);
        char buffer[64];
        std::strftime(buffer, sizeof(buffer), format.c_str(), tm);
        return std::string(buffer);
    }
    // Test if two timepoints are on the same day
     inline bool isSameDay(const std::chrono::system_clock::time_point& tp1, const std::chrono::system_clock::time_point& tp2) {
        // Convert time_point to time_t
        std::time_t time1 = std::chrono::system_clock::to_time_t(tp1);
        std::time_t time2 = std::chrono::system_clock::to_time_t(tp2);

        // Convert time_t to tm struct
        std::tm tm1 = *std::localtime(&time1);
        std::tm tm2 = *std::localtime(&time2);

        // Compare year, month, and day
        return (tm1.tm_year == tm2.tm_year &&
                tm1.tm_mon == tm2.tm_mon &&
                tm1.tm_mday == tm2.tm_mday);
    }

} // namespace DateTimeConverter

#endif // DATE_TIME_H
