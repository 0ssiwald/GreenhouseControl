#ifndef DATE_TIME_H
#define DATE_TIME_H
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

// To make timezone adjustment on windows and posix
//#ifdef _WIN32
//#define timegm _mkgmtime
//#endif

#define timegm _mkgmtime

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

/*
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <stdexcept>

// Include necessary headers for platform-specific functions
// All this is necessary because timezone adjustment on Windows and Posix works diffrent
#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
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
    // Convert to time_t assuming the time is in UTC
    tm.tm_isdst = -1; // Disable daylight saving time adjustment
    std::time_t time_val;
#ifdef _WIN32
    time_val = _mkgmtime(&tm); // Use _mkgmtime to avoid timezone adjustment on Windows
#else
    time_val = timegm(&tm); // Use timegm to avoid timezone adjustment on POSIX systems
#endif
    if (time_val == -1) {
        throw std::runtime_error("Failed to convert tm to time_t");
    }
    return std::chrono::system_clock::from_time_t(time_val);
}

// Convert time_point to string
inline std::string timePointToString(const std::chrono::system_clock::time_point& timePoint, const std::string& format = "%d.%m.%Y %H:%M:%S") {
    std::time_t time_val = std::chrono::system_clock::to_time_t(timePoint);
#ifdef _WIN32
    std::tm tm;
    gmtime_s(&tm, &time_val); // Use gmtime_s on Windows
#else
    std::tm* tm = std::gmtime(&time_val); // Use gmtime on POSIX systems
#endif
    char buffer[64];
#ifdef _WIN32
    std::strftime(buffer, sizeof(buffer), format.c_str(), &tm);
#else
    std::strftime(buffer, sizeof(buffer), format.c_str(), tm);
#endif
    return std::string(buffer);
}

// Test if two timepoints are on the same day
inline bool isSameDay(const std::chrono::system_clock::time_point& tp1, const std::chrono::system_clock::time_point& tp2) {
    // Convert time_point to time_t
    std::time_t time1 = std::chrono::system_clock::to_time_t(tp1);
    std::time_t time2 = std::chrono::system_clock::to_time_t(tp2);

// Convert time_t to tm struct using gmtime
#ifdef _WIN32
    std::tm tm1, tm2;
    gmtime_s(&tm1, &time1); // Use gmtime_s on Windows
    gmtime_s(&tm2, &time2); // Use gmtime_s on Windows
#else
    std::tm* tm1 = std::gmtime(&time1); // Use gmtime on POSIX systems
    std::tm* tm2 = std::gmtime(&time2); // Use gmtime on POSIX systems
#endif

// Compare year, month, and day
#ifdef _WIN32
    return (tm1.tm_year == tm2.tm_year &&
            tm1.tm_mon == tm2.tm_mon &&
            tm1.tm_mday == tm2.tm_mday);
#else
    return (tm1->tm_year == tm2->tm_year &&
            tm1->tm_mon == tm2->tm_mon &&
            tm1->tm_mday == tm2->tm_mday);
#endif
}

} // namespace DateTimeConverter
*/

#endif // DATE_TIME_H
