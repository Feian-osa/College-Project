/*
    ReportWriter.h
    Report generation module for inventory analysis and reporting
*/

#ifndef REPORT_WRITER_H
#define REPORT_WRITER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Inventory.h"
#include "Utilities.h"

// Avoid `using namespace std;` in headers to prevent symbol pollution in consumers

// ===== ReportWriter Class =====
// Handles all report generation tasks

class ReportWriter {
private:
    const InventoryManager& inventoryManager;  // Reference to inventory
    std::string reportDir;                     // Directory to save reports
    
    // Private helper: Generate filename with timestamp
    std::string generateReportFilename(const std::string& reportType);

public:
    // Constructor
    ReportWriter(const InventoryManager& manager, const std::string& dir = "Reports/");
    
    // ===== Report Generation Methods =====
    
    // Generate complete inventory report
    void generateInventoryReport();
    
    // Generate low stock report
    void generateLowStockReport();
    
    // Generate inventory value report
    void generateInventoryValueReport();
    
    // Generate category-wise report
    void generateCategoryReport();
    
    // Display quick summary to console
    void displayInventorySummary() const;
};

#endif // REPORT_WRITER_H
