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

using namespace std;

// ===== InventoryItem Class =====
// Represents a single item in the warehouse inventory

class InventoryItem {
private:
    string itemID;           // Unique item identifier (e.g., ITM001)
    string itemName;         // Name of the item
    string category;         // Category (e.g., Electronics, Parts)
    int quantity;            // Current stock quantity
    int reorderLevel;        // Minimum quantity before alert
    double unitPrice;        // Price per unit
    string entryDate;        // Date when item was added

public:
    // Constructor
    InventoryItem();
    
    // ===== Getters =====
    string getItemID() const { return itemID; }
    string getItemName() const { return itemName; }
    string getCategory() const { return category; }
    int getQuantity() const { return quantity; }
    int getReorderLevel() const { return reorderLevel; }
    double getUnitPrice() const { return unitPrice; }
    string getEntryDate() const { return entryDate; }
    
    // Calculate total value of this item (quantity * unitPrice)
    double getTotalValue() const { return quantity * unitPrice; }
    
    // Check if item is low stock
    bool isLowStock() const { return quantity <= reorderLevel; }
    
    // ===== Setters =====
    void setItemID(const string& id) { itemID = id; }
    void setItemName(const string& name) { itemName = name; }
    void setCategory(const string& cat) { category = cat; }
    void setQuantity(int qty) { quantity = qty; }
    void setReorderLevel(int level) { reorderLevel = level; }
    void setUnitPrice(double price) { unitPrice = price; }
    void setEntryDate(const string& date) { entryDate = date; }
    
    // Display item in table format
    void display() const;
    
    // Convert item to file format (for saving)
    string toFileString() const;
    
    // Parse item from file format (for loading)
    void fromFileString(const string& data);
};


// ===== InventoryManager Class =====
// Manages all inventory operations (CRUD)

class InventoryManager {
private:
    vector<InventoryItem> items;        // Container for all items
    string inventoryFile;               // Filename for persistent storage
    
    // Private helper functions
    void loadInventory();               // Load items from file
    void saveInventory();               // Save items to file
    InventoryItem* findItemByID(const string& id);  // Search by ID
    
public:
    // Constructor and Destructor
    InventoryManager(const string& filename = "inventory.txt");
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
    const vector<InventoryItem>& getAllItems() const { return items; }
    
    // Get total number of items
    int getTotalItemsCount() const { return items.size(); }
    
    // Get total inventory value
    double getTotalInventoryValue() const;
    
    // Get a specific item by ID (for reports)
    const InventoryItem* getItemByID(const string& id) const;
};

#endif // INVENTORY_H