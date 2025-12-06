/*
    LowStockAlert.cpp
    Implementation of Low Stock Alert module
*/

#include "LowStockAlert.h"
#include <iostream>
#include <vector>

using namespace std;

// ========== LowStockAlert Implementation ==========

// Constructor
LowStockAlert::LowStockAlert(const InventoryManager& manager, int threshold)
    : inventoryManager(manager), defaultThreshold(threshold) {}

// Display individual alert
void LowStockAlert::displayAlert(const InventoryItem& item, int threshold) const {
    int shortage = threshold - item.getQuantity();
    
    cout << "\n⚠️  LOW STOCK ALERT\n";
    cout << "  Item ID: " << item.getItemID() << "\n";
    cout << "  Name: " << item.getItemName() << "\n";
    cout << "  Current Stock: " << item.getQuantity() << " units\n";
    cout << "  Reorder Level: " << threshold << " units\n";
    cout << "  Units Short: " << shortage << " units\n";
}

// Check low stock items with default threshold
void LowStockAlert::checkLowStockItems() {
    checkLowStockItemsWithThreshold(defaultThreshold);
}

// Check low stock items with custom threshold
void LowStockAlert::checkLowStockItemsWithThreshold(int threshold) {
    printHeader("LOW STOCK CHECK");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items in inventory.\n";
        return;
    }

    vector<InventoryItem> lowStockItems;
    
    for (const auto& item : items) {
        if (item.getQuantity() <= threshold) {
            lowStockItems.push_back(item);
        }
    }

    if (lowStockItems.empty()) {
        cout << "\n✅ All items are well stocked!\n";
        cout << "   Current threshold: " << threshold << " units\n";
        return;
    }

    cout << "\n⚠️  ITEMS BELOW THRESHOLD (" << threshold << " units):\n\n";
    
    cout << left << setw(12) << "Item ID"
         << setw(25) << "Item Name"
         << setw(10) << "Qty"
         << setw(12) << "Threshold"
         << setw(12) << "Short By\n";
    cout << string(71, '-') << "\n";

    for (const auto& item : lowStockItems) {
        int shortage = threshold - item.getQuantity();
        cout << left << setw(12) << item.getItemID()
             << setw(25) << (item.getItemName().length() > 24 ? 
                           item.getItemName().substr(0, 21) + "..." : item.getItemName())
             << setw(10) << item.getQuantity()
             << setw(12) << threshold
             << shortage << " units\n";
    }

    cout << "\n" << string(71, '-') << "\n";
    cout << "📌 Action Required: " << lowStockItems.size() << " item(s) need restocking.\n";
}

// Get list of low stock items
vector<InventoryItem> LowStockAlert::getLowStockItems(int threshold) const {
    const auto& items = inventoryManager.getAllItems();
    vector<InventoryItem> result;

    int checkThreshold = (threshold == -1) ? defaultThreshold : threshold;

    for (const auto& item : items) {
        if (item.getQuantity() <= checkThreshold) {
            result.push_back(item);
        }
    }

    return result;
}

// Display alert summary
void LowStockAlert::displayAlertSummary() {
    printHeader("LOW STOCK ALERT SUMMARY");

    const auto& items = inventoryManager.getAllItems();
    
    if (items.empty()) {
        cout << "No items in inventory.\n";
        return;
    }

    vector<InventoryItem> lowStockItems = getLowStockItems();
    vector<InventoryItem> criticalItems;

    // Items at or below 50% of reorder level are critical
    for (const auto& item : lowStockItems) {
        if (item.getQuantity() <= item.getReorderLevel() / 2) {
            criticalItems.push_back(item);
        }
    }

    cout << "\n📊 ALERT STATISTICS:\n";
    cout << "  Total Items: " << items.size() << "\n";
    cout << "  Items Below Threshold (" << defaultThreshold << "): " << lowStockItems.size() << "\n";
    cout << "  Critical Items (≤50% of reorder): " << criticalItems.size() << "\n";

    if (!lowStockItems.empty()) {
        cout << "\n⚠️  ITEMS REQUIRING ATTENTION:\n\n";
        
        for (const auto& item : lowStockItems) {
            string urgency = "NORMAL";
            if (item.getQuantity() <= item.getReorderLevel() / 2) {
                urgency = "🔴 CRITICAL";
            } else if (item.getQuantity() == 0) {
                urgency = "⛔ OUT OF STOCK";
            }
            
            cout << "  " << urgency << " - " << item.getItemID() 
                 << " (" << item.getItemName() << "): " 
                 << item.getQuantity() << "/" << item.getReorderLevel() << " units\n";
        }
    } else {
        cout << "\n✅ No alerts at this time. Inventory is healthy!\n";
    }

    cout << "\n" << string(70, '=') << "\n";
}
