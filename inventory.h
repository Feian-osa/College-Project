/*
    Inventory.h
    Core inventory data structure and management
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <iostream>
#include "Utilities.h"

// Avoid `using namespace std;` in headers to prevent symbol pollution in consumers

// ===== InventoryItem Class =====
// Represents a single item in the warehouse inventory

class InventoryItem {
private:
    std::string itemID;           // Unique item identifier (e.g., ITM001)
    std::string itemName;         // Name of the item
    std::string category;         // Category (e.g., Electronics, Parts)
    int quantity;            // Current stock quantity
    int reorderLevel;        // Minimum quantity before alert
    double unitPrice;        // Price per unit
    std::string entryDate;        // Date when item was added

public:
    // Constructor
    InventoryItem();
    
    // ===== Getters =====
    std::string getItemID() const { return itemID; }
    std::string getItemName() const { return itemName; }
    std::string getCategory() const { return category; }
    int getQuantity() const { return quantity; }
    int getReorderLevel() const { return reorderLevel; }
    double getUnitPrice() const { return unitPrice; }
    std::string getEntryDate() const { return entryDate; }
    
    // Calculate total value of this item (quantity * unitPrice)
    double getTotalValue() const { return quantity * unitPrice; }
    
    // Check if item is low stock
    bool isLowStock() const { return quantity <= reorderLevel; }
    
    // ===== Setters =====
    void setItemID(const std::string& id) { itemID = id; }
    void setItemName(const std::string& name) { itemName = name; }
    void setCategory(const std::string& cat) { category = cat; }
    void setQuantity(int qty) { quantity = qty; }
    void setReorderLevel(int level) { reorderLevel = level; }
    void setUnitPrice(double price) { unitPrice = price; }
    void setEntryDate(const std::string& date) { entryDate = date; }
    
    // Display item in table format
    void display() const;
    
    // Convert item to file format (for saving)
    std::string toFileString() const;
    
    // Parse item from file format (for loading)
    void fromFileString(const std::string& data);
};


// ===== InventoryManager Class =====
// Manages all inventory operations (CRUD)

class InventoryManager {
private:
    std::vector<InventoryItem> items;        // Container for all items
    std::string inventoryFile;               // Filename for persistent storage
    
    // Private helper functions
    void loadInventory();               // Load items from file
    void saveInventory();               // Save items to file
    InventoryItem* findItemByID(const std::string& id);  // Search by ID
    
public:
    // Constructor and Destructor
    InventoryManager(const std::string& filename = "inventory.txt");
    ~InventoryManager();
    
    // ===== CRUD Operations =====
    
    // CREATE: Add a new item to inventory
    void addNewItem();
    
    // READ: Display all items
    void viewAllItems() const;
    
    // READ: Search for items by ID, name, or category
    void searchItem() const;
    
    // UPDATE: Modify existing item details
    void updateItem();
    
    // UPDATE: Adjust stock quantity (add/remove)
    void performStockInOut();
    
    // DELETE: Remove an item from inventory
    void deleteItem();
    
    // ===== Getters for other modules =====
    
    // Get all items (used by Report and Alert modules)
    const std::vector<InventoryItem>& getAllItems() const { return items; }
    
    // Get total number of items
    int getTotalItemsCount() const { return items.size(); }
    
    // Get total inventory value
    double getTotalInventoryValue() const;
    
    // Get a specific item by ID (for reports)
    const InventoryItem* getItemByID(const std::string& id) const;
};

#endif // INVENTORY_H