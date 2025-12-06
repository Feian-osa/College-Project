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
#include <iostream>

using namespace std;

// ===== Utility Functions =====

// Get current date in YYYY-MM-DD format
inline string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

// Get current date and time in YYYY-MM-DD HH:MM:SS format
inline string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday << " "
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec;
    return ss.str();
}

// Convert string to lowercase
inline string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Print a separator line
inline void printSeparator(int width = 70) {
    cout << string(width, '=') << "\n";
}

// Print a section header
inline void printHeader(const string& title) {
    printSeparator();
    cout << "  " << title << "\n";
    printSeparator();
}

#endif // UTILITIES_H
