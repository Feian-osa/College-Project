/*
    LowStockAlert.h
    Low stock alert and notification system
*/

#ifndef LOW_STOCK_ALERT_H
#define LOW_STOCK_ALERT_H

#include <string>
#include <vector>
#include <iostream>
#include "Inventory.h"
#include "Utilities.h"

using namespace std;

// ===== LowStockAlert Class =====
// Manages low stock monitoring and alerts

class LowStockAlert {
private:
    const InventoryManager& inventoryManager;  // Reference to inventory
    int defaultThreshold;                      // Default low stock threshold
    
    // Helper function to display an alert
    void displayAlert(const InventoryItem& item, int threshold) const;

public:
    // Constructor
    LowStockAlert(const InventoryManager& manager, int threshold = 10);
    
    // ===== Alert Methods =====
    
    // Check and display all low stock items
    void checkLowStockItems();
    
    // Check with custom threshold
    void checkLowStockItemsWithThreshold(int threshold);
    
    // Get list of low stock items
    vector<InventoryItem> getLowStockItems(int threshold = -1) const;
    
    // Set default threshold
    void setDefaultThreshold(int threshold) { defaultThreshold = threshold; }
    
    // Get current threshold
    int getDefaultThreshold() const { return defaultThreshold; }
    
    // Display alert summary
    void displayAlertSummary();
};

#endif // LOW_STOCK_ALERT_H
