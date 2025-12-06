/*
    Utilities.h
    Shared utility functions and constants used across all modules
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

// ===== Utility Functions =====

// Get current date in YYYY-MM-DD format
inline std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "-"
       << std::setw(2) << std::setfill('0') << ltm->tm_mday;
    return ss.str();
}

// Get current date and time in YYYY-MM-DD HH:MM:SS format
inline std::string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "-"
       << std::setw(2) << std::setfill('0') << ltm->tm_mday << " "
       << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << ltm->tm_min << ":"
       << std::setw(2) << std::setfill('0') << ltm->tm_sec;
    return ss.str();
}

// Convert string to lowercase
inline std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Print a separator line
inline void printSeparator(int width = 70) {
    std::cout << std::string(width, '=') << "\n";
}

// Print a section header
inline void printHeader(const std::string& title) {
    printSeparator();
    std::cout << "  " << title << "\n";
    printSeparator();
}

#endif // UTILITIES_H
