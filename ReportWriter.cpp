/*
    ReportWriter.cpp
    Implementation of Report Writing module
*/

#include "ReportWriter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

// ========== ReportWriter Implementation ==========

// Constructor
ReportWriter::ReportWriter(const InventoryManager& manager, const string& dir) 
    : inventoryManager(manager), reportDir(dir) {}

// Generate report filename with timestamp
string ReportWriter::generateReportFilename(const string& reportType) {
    stringstream ss;
    ss << reportDir << reportType << "_" << getCurrentDate() << ".txt";
    return ss.str();
}

// Generate complete inventory report
void ReportWriter::generateInventoryReport() {
    printHeader("GENERATING INVENTORY REPORT");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items to report.\n";
        return;
    }

    string filename = generateReportFilename("Inventory_Report");
    ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file: " << filename << "\n";
        return;
    }

    // Write report header
    reportFile << "=" << string(68, '=') << "\n";
    reportFile << "  WAREHOUSE INVENTORY REPORT\n";
    reportFile << "  Generated: " << getCurrentDateTime() << "\n";
    reportFile << "=" << string(68, '=') << "\n\n";

    // Write items in tabular format
    reportFile << left << setw(12) << "Item ID" 
               << setw(25) << "Item Name" 
               << setw(15) << "Category" 
               << setw(10) << "Qty" 
               << setw(12) << "Entry Date"
               << setw(15) << "Reorder Lvl"
               << setw(12) << "Price\n";
    reportFile << string(102, '-') << "\n";

    double totalValue = 0;
    int totalQty = 0;

    for (const auto& item : items) {
        reportFile << left << setw(12) << item.getItemID()
                   << setw(25) << (item.getItemName().length() > 24 ? 
                                 item.getItemName().substr(0, 21) + "..." : item.getItemName())
                   << setw(15) << (item.getCategory().length() > 14 ? 
                                 item.getCategory().substr(0, 11) + "..." : item.getCategory())
                   << setw(10) << item.getQuantity()
                   << setw(12) << item.getEntryDate()
                   << setw(15) << item.getReorderLevel()
                   << "$" << fixed << setprecision(2) << setw(10) << item.getUnitPrice() << "\n";
        
        totalValue += item.getTotalValue();
        totalQty += item.getQuantity();
    }

    reportFile << "\n" << string(102, '-') << "\n";
    reportFile << "SUMMARY:\n";
    reportFile << "  Total Item Types: " << items.size() << "\n";
    reportFile << "  Total Quantity: " << totalQty << "\n";
    reportFile << "  Total Inventory Value: $" << fixed << setprecision(2) << totalValue << "\n";
    reportFile << "=" << string(68, '=') << "\n";

    reportFile.close();

    cout << "\n✅ Inventory Report generated: " << filename << "\n";
    cout << "   Total Items: " << items.size() << "\n";
    cout << "   Total Value: $" << fixed << setprecision(2) << totalValue << "\n";
}

// Generate low stock report
void ReportWriter::generateLowStockReport() {
    printHeader("GENERATING LOW STOCK REPORT");

    const auto& items = inventoryManager.getAllItems();
    
    vector<InventoryItem> lowStockItems;
    for (const auto& item : items) {
        if (item.isLowStock()) {
            lowStockItems.push_back(item);
        }
    }

    string filename = generateReportFilename("LowStock_Report");
    ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file: " << filename << "\n";
        return;
    }

    // Write report header
    reportFile << "=" << string(68, '=') << "\n";
    reportFile << "  LOW STOCK ALERT REPORT\n";
    reportFile << "  Generated: " << getCurrentDateTime() << "\n";
    reportFile << "=" << string(68, '=') << "\n\n";

    if (lowStockItems.empty()) {
        reportFile << "✅ No low stock items detected!\n";
    } else {
        reportFile << "ATTENTION: The following items are below reorder level:\n\n";
        
        reportFile << left << setw(12) << "Item ID" 
                   << setw(25) << "Item Name" 
                   << setw(10) << "Qty"
                   << setw(15) << "Reorder Lvl"
                   << setw(15) << "Units Short\n";
        reportFile << string(77, '-') << "\n";

        for (const auto& item : lowStockItems) {
            int shortage = item.getReorderLevel() - item.getQuantity();
            reportFile << left << setw(12) << item.getItemID()
                       << setw(25) << (item.getItemName().length() > 24 ? 
                                     item.getItemName().substr(0, 21) + "..." : item.getItemName())
                       << setw(10) << item.getQuantity()
                       << setw(15) << item.getReorderLevel()
                       << shortage << "\n";
        }

        reportFile << "\n" << string(77, '-') << "\n";
        reportFile << "SUMMARY: " << lowStockItems.size() << " item(s) need restocking.\n";
    }

    reportFile << "=" << string(68, '=') << "\n";

    reportFile.close();

    cout << "\n✅ Low Stock Report generated: " << filename << "\n";
    if (!lowStockItems.empty()) {
        cout << "   Items requiring attention: " << lowStockItems.size() << "\n";
    } else {
        cout << "   Status: All items well stocked!\n";
    }
}

// Generate inventory value report
void ReportWriter::generateInventoryValueReport() {
    printHeader("GENERATING INVENTORY VALUE REPORT");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items to report.\n";
        return;
    }

    string filename = generateReportFilename("InventoryValue_Report");
    ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file: " << filename << "\n";
        return;
    }

    // Write report header
    reportFile << "=" << string(68, '=') << "\n";
    reportFile << "  INVENTORY VALUE ANALYSIS\n";
    reportFile << "  Generated: " << getCurrentDateTime() << "\n";
    reportFile << "=" << string(68, '=') << "\n\n";

    reportFile << left << setw(12) << "Item ID" 
               << setw(25) << "Item Name" 
               << setw(10) << "Qty"
               << setw(12) << "Price"
               << setw(15) << "Total Value\n";
    reportFile << string(79, '-') << "\n";

    double totalValue = 0;

    for (const auto& item : items) {
        double itemValue = item.getTotalValue();
        reportFile << left << setw(12) << item.getItemID()
                   << setw(25) << (item.getItemName().length() > 24 ? 
                                 item.getItemName().substr(0, 21) + "..." : item.getItemName())
                   << setw(10) << item.getQuantity()
                   << "$" << setw(11) << fixed << setprecision(2) << item.getUnitPrice()
                   << "$" << fixed << setprecision(2) << itemValue << "\n";
        
        totalValue += itemValue;
    }

    reportFile << "\n" << string(79, '-') << "\n";
    reportFile << "TOTAL INVENTORY VALUE: $" << fixed << setprecision(2) << totalValue << "\n";
    reportFile << "=" << string(68, '=') << "\n";

    reportFile.close();

    cout << "\n✅ Inventory Value Report generated: " << filename << "\n";
    cout << "   Total Value: $" << fixed << setprecision(2) << totalValue << "\n";
}

// Generate category-wise report
void ReportWriter::generateCategoryReport() {
    printHeader("GENERATING CATEGORY-WISE REPORT");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items to report.\n";
        return;
    }

    // Group items by category
    map<string, vector<InventoryItem>> categoryMap;
    for (const auto& item : items) {
        categoryMap[item.getCategory()].push_back(item);
    }

    string filename = generateReportFilename("Category_Report");
    ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file: " << filename << "\n";
        return;
    }

    // Write report header
    reportFile << "=" << string(68, '=') << "\n";
    reportFile << "  CATEGORY-WISE INVENTORY REPORT\n";
    reportFile << "  Generated: " << getCurrentDateTime() << "\n";
    reportFile << "=" << string(68, '=') << "\n\n";

    for (const auto& categoryPair : categoryMap) {
        string category = categoryPair.first;
        const auto& categoryItems = categoryPair.second;

        reportFile << "\nCATEGORY: " << category << "\n";
        reportFile << string(70, '-') << "\n";

        double categoryValue = 0;
        int categoryQty = 0;

        reportFile << left << setw(12) << "Item ID" 
                   << setw(25) << "Item Name" 
                   << setw(10) << "Qty"
                   << setw(12) << "Price"
                   << setw(15) << "Value\n";
        reportFile << string(79, '-') << "\n";

        for (const auto& item : categoryItems) {
            double itemValue = item.getTotalValue();
            reportFile << left << setw(12) << item.getItemID()
                       << setw(25) << (item.getItemName().length() > 24 ? 
                                     item.getItemName().substr(0, 21) + "..." : item.getItemName())
                       << setw(10) << item.getQuantity()
                       << "$" << setw(11) << fixed << setprecision(2) << item.getUnitPrice()
                       << "$" << fixed << setprecision(2) << itemValue << "\n";
            
            categoryValue += itemValue;
            categoryQty += item.getQuantity();
        }

        reportFile << "\nCategory Summary:\n";
        reportFile << "  Items in Category: " << categoryItems.size() << "\n";
        reportFile << "  Total Quantity: " << categoryQty << "\n";
        reportFile << "  Category Value: $" << fixed << setprecision(2) << categoryValue << "\n";
    }

    reportFile << "\n" << "=" << string(68, '=') << "\n";
    reportFile << "TOTAL CATEGORIES: " << categoryMap.size() << "\n";
    reportFile << "=" << string(68, '=') << "\n";

    reportFile.close();

    cout << "\n✅ Category Report generated: " << filename << "\n";
    cout << "   Total Categories: " << categoryMap.size() << "\n";
}

// Display quick summary to console
void ReportWriter::displayInventorySummary() const {
    printHeader("INVENTORY SUMMARY");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items in inventory.\n";
        return;
    }

    // Calculate statistics
    double totalValue = 0;
    int totalQty = 0;
    int lowStockCount = 0;

    for (const auto& item : items) {
        totalValue += item.getTotalValue();
        totalQty += item.getQuantity();
        if (item.isLowStock()) lowStockCount++;
    }

    cout << "\n📊 INVENTORY STATISTICS:\n";
    cout << "  Total Item Types: " << items.size() << "\n";
    cout << "  Total Units in Stock: " << totalQty << "\n";
    cout << "  Total Inventory Value: $" << fixed << setprecision(2) << totalValue << "\n";
    cout << "  Items at Low Stock: " << lowStockCount << "\n";

    // Category breakdown
    map<string, int> categoryCount;
    for (const auto& item : items) {
        categoryCount[item.getCategory()]++;
    }

    cout << "\n📦 CATEGORIES:\n";
    for (const auto& catPair : categoryCount) {
        cout << "  " << catPair.first << ": " << catPair.second << " item(s)\n";
    }
}
