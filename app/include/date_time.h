#ifndef DATE_TIME_H
#define DATE_TIME_H
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

// To make timezone adjustment on windows and posix
#ifdef _WIN32
#define timegm _mkgmtime
#endif

namespace DateTimeConverter {

    // Convert string to time_point
    inline std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeStr, const std::string& format = "%d.%m.%Y %H:%M:%S") {
        std::tm tm = {};
        std::istringstream ss(dateTimeStr);
        ss >> std::get_time(&tm, format.c_str());
        if (ss.fail()) {
            throw std::invalid_argument("Invalid date/time string: " + dateTimeStr);
        }
        tm.tm_isdst = -1; // Disable daylight saving time adjustment
        std::time_t time_val = timegm(&tm); // Use timegm to avoid timezone adjustment
        if (time_val == -1) {
            throw std::runtime_error("Failed to convert tm to time_t");
        }
        return std::chrono::system_clock::from_time_t(time_val);
    }

    // Convert time_point to string
    inline std::string timePointToString(const std::chrono::system_clock::time_point& timePoint, const std::string& format = "%d.%m.%Y %H:%M:%S") {
        std::time_t time_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::gmtime(&time_val); // Use gmtime to convert to UTC
        std::ostringstream oss;
        oss << std::put_time(&tm, format.c_str());
        return oss.str();
    }

    // Test if two timepoints are on the same day
    inline bool isSameDay(const std::chrono::system_clock::time_point& tp1, const std::chrono::system_clock::time_point& tp2) {
        auto time1 = std::chrono::system_clock::to_time_t(tp1);
        auto time2 = std::chrono::system_clock::to_time_t(tp2);
        std::tm tm1 = *std::gmtime(&time1);
        std::tm tm2 = *std::gmtime(&time2);
        return (tm1.tm_year == tm2.tm_year && tm1.tm_mon == tm2.tm_mon && tm1.tm_mday == tm2.tm_mday);
    }

} // namespace DateTimeConverter

#endif // DATE_TIME_H
