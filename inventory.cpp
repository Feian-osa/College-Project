/*
    Inventory.cpp
    Implementation of InventoryItem and InventoryManager classes
*/

#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// ========== InventoryItem Implementation ==========

// Constructor - Initialize with default values
InventoryItem::InventoryItem() 
    : quantity(0), reorderLevel(10), unitPrice(0.0) {}

// Display item in formatted table row
void InventoryItem::display() const {
    cout << left << setw(12) << itemID 
         << setw(25) << (itemName.length() > 24 ? itemName.substr(0, 21) + "..." : itemName)
         << setw(15) << (category.length() > 14 ? category.substr(0, 11) + "..." : category)
         << setw(10) << quantity 
         << setw(12) << entryDate 
         << setw(15) << reorderLevel
         << "$" << fixed << setprecision(2) << setw(8) << unitPrice << endl;
}

// Convert item to pipe-delimited format for file storage
string InventoryItem::toFileString() const {
    stringstream ss;
    ss << itemID << "|" << itemName << "|" << category << "|" 
       << quantity << "|" << entryDate << "|" << reorderLevel << "|" << unitPrice;
    return ss.str();
}

// Parse item from pipe-delimited format
void InventoryItem::fromFileString(const string& data) {
    stringstream ss(data);
    string temp;
    
    getline(ss, itemID, '|');
    getline(ss, itemName, '|');
    getline(ss, category, '|');
    
    getline(ss, temp, '|');
    quantity = stoi(temp);
    
    getline(ss, entryDate, '|');
    
    getline(ss, temp, '|');
    reorderLevel = stoi(temp);
    
    getline(ss, temp);
    if (!temp.empty()) {
        unitPrice = stod(temp);
    }
}


// ========== InventoryManager Implementation ==========

// Constructor - Load existing inventory from file
InventoryManager::InventoryManager(const string& filename) 
    : inventoryFile(filename) {
    loadInventory();
}

// Destructor - Save inventory to file
InventoryManager::~InventoryManager() {
    saveInventory();
}

// Load all items from persistent storage
void InventoryManager::loadInventory() {
    items.clear();
    ifstream file(inventoryFile);
    if (!file.is_open()) {
        // File doesn't exist yet - this is OK for new systems
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                InventoryItem item;
                item.fromFileString(line);
                items.push_back(item);
            } catch (const exception& e) {
                cerr << "Warning: Error reading line: " << line << endl;
            }
        }
    }
    file.close();
}

// Save all items to persistent storage
void InventoryManager::saveInventory() {
    ofstream file(inventoryFile);
    if (!file.is_open()) {
        cout << "Error: Could not save inventory data to " << inventoryFile << "!\n";
        return;
    }

    for (const auto& item : items) {
        file << item.toFileString() << endl;
    }
    file.close();
}

// Find item by ID - returns pointer to item or nullptr if not found
InventoryItem* InventoryManager::findItemByID(const string& id) {
    string searchID = toLower(id);
    for (auto& item : items) {
        if (toLower(item.getItemID()) == searchID) {
            return &item;
        }
    }
    return nullptr;
}

// Get const pointer to item (for reports and alerts)
const InventoryItem* InventoryManager::getItemByID(const string& id) const {
    string searchID = toLower(id);
    for (const auto& item : items) {
        if (toLower(item.getItemID()) == searchID) {
            return &item;
        }
    }
    return nullptr;
}

// Calculate total inventory value
double InventoryManager::getTotalInventoryValue() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.getTotalValue();
    }
    return total;
}

// ===== CRUD Operations =====

// CREATE: Add a new item
void InventoryManager::addNewItem() {
    printHeader("ADD NEW ITEM");

    InventoryItem newItem;
    string input;

    // Get Item ID with duplicate check
    bool duplicate;
    do {
        duplicate = false;
        cout << "Item ID (e.g., ITM001): ";
        getline(cin, input);
        
        if (input.empty()) {
            cout << "  Error: Item ID cannot be empty!\n";
            duplicate = true;
            continue;
        }
        
        if (findItemByID(input) != nullptr) {
            cout << "  Error: Item ID already exists!\n";
            duplicate = true;
        }
    } while (duplicate);
    newItem.setItemID(input);

    // Get Item Name
    cout << "Item Name: ";
    getline(cin, input);
    while (input.empty()) {
        cout << "  Error: Item Name cannot be empty!\n";
        cout << "Item Name: ";
        getline(cin, input);
    }
    newItem.setItemName(input);

    // Get Category
    cout << "Category (e.g., Electronics): ";
    getline(cin, input);
    newItem.setCategory(input.empty() ? "Uncategorized" : input);

    // Get Quantity
    cout << "Quantity: ";
    while (true) {
        getline(cin, input);
        try {
            int qty = stoi(input);
            if (qty < 0) {
                cout << "  Error: Quantity cannot be negative!\n";
                cout << "Quantity: ";
                continue;
            }
            newItem.setQuantity(qty);
            break;
        } catch (...) {
            cout << "  Error: Please enter a valid number!\n";
            cout << "Quantity: ";
        }
    }

    // Get Reorder Level
    cout << "Reorder Level (default 10): ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            int reorder = stoi(input);
            if (reorder < 0) reorder = 0;
            newItem.setReorderLevel(reorder);
        } catch (...) {
            newItem.setReorderLevel(10);
        }
    } else {
        newItem.setReorderLevel(10);
    }

    // Get Unit Price
    cout << "Unit Price: $";
    while (true) {
        getline(cin, input);
        try {
            double price = stod(input);
            if (price < 0) {
                cout << "  Error: Price cannot be negative!\n";
                cout << "Unit Price: $";
                continue;
            }
            newItem.setUnitPrice(price);
            break;
        } catch (...) {
            cout << "  Error: Please enter a valid price!\n";
            cout << "Unit Price: $";
        }
    }

    newItem.setEntryDate(getCurrentDate());

    items.push_back(newItem);
    saveInventory();

    cout << "\n✅ Item added successfully! ID: " << newItem.getItemID() << "\n";
}

// READ: View all items
void InventoryManager::viewAllItems() const {
    if (items.empty()) {
        cout << "\n⚠️  No items in inventory.\n";
        return;
    }

    printHeader("ALL INVENTORY ITEMS");

    cout << left << setw(12) << "Item ID" 
         << setw(25) << "Item Name" 
         << setw(15) << "Category" 
         << setw(10) << "Qty" 
         << setw(12) << "Entry Date"
         << setw(15) << "Reorder Level"
         << setw(10) << "Price" << endl;
    cout << string(100, '-') << endl;

    for (const auto& item : items) {
        item.display();
    }

    cout << "\nTotal Items: " << items.size() << endl;
    cout << "Total Inventory Value: $" << fixed << setprecision(2) 
         << getTotalInventoryValue() << endl;
}

// READ: Search for items
void InventoryManager::searchItem() const {
    printHeader("SEARCH ITEM");

    int searchChoice;
    cout << "Search by:\n";
    cout << "  1. Item ID\n";
    cout << "  2. Item Name\n";
    cout << "  3. Category\n";
    cout << "Enter choice (1-3): ";
    
    string choiceInput;
    getline(cin, choiceInput);
    try {
        searchChoice = stoi(choiceInput);
    } catch (...) {
        cout << "❌ Invalid choice!\n";
        return;
    }

    if (searchChoice < 1 || searchChoice > 3) {
        cout << "❌ Invalid choice!\n";
        return;
    }

    string searchTerm;
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    vector<InventoryItem> results;
    string searchLower = toLower(searchTerm);

    for (const auto& item : items) {
        bool match = false;
        switch (searchChoice) {
            case 1: // Search by ID
                match = toLower(item.getItemID()).find(searchLower) != string::npos;
                break;
            case 2: // Search by Name
                match = toLower(item.getItemName()).find(searchLower) != string::npos;
                break;
            case 3: // Search by Category
                match = toLower(item.getCategory()).find(searchLower) != string::npos;
                break;
        }
        
        if (match) {
            results.push_back(item);
        }
    }

    if (results.empty()) {
        cout << "\n❌ No items found.\n";
        return;
    }

    cout << "\n✅ Found " << results.size() << " item(s):\n\n";
    cout << left << setw(12) << "Item ID" 
         << setw(25) << "Item Name" 
         << setw(15) << "Category" 
         << setw(10) << "Qty" 
         << setw(12) << "Entry Date"
         << setw(15) << "Reorder Level"
         << setw(10) << "Price" << endl;
    cout << string(100, '-') << endl;

    for (const auto& item : results) {
        item.display();
    }
}

// UPDATE: Modify item details
void InventoryManager::updateItem() {
    string searchID;
    cout << "\nEnter Item ID to update: ";
    getline(cin, searchID);

    InventoryItem* item = findItemByID(searchID);
    if (item == nullptr) {
        cout << "❌ Item not found!\n";
        return;
    }

    printHeader("UPDATE ITEM DETAILS");
    cout << "Current Details:\n";
    cout << "  Name: " << item->getItemName() << "\n";
    cout << "  Category: " << item->getCategory() << "\n";
    cout << "  Quantity: " << item->getQuantity() << "\n";
    cout << "  Reorder Level: " << item->getReorderLevel() << "\n";
    cout << "  Unit Price: $" << fixed << setprecision(2) << item->getUnitPrice() << "\n";
    cout << "\nPress Enter to keep current value\n\n";

    string input;

    // Update Name
    cout << "New name [" << item->getItemName() << "]: ";
    getline(cin, input);
    if (!input.empty()) item->setItemName(input);

    // Update Category
    cout << "New category [" << item->getCategory() << "]: ";
    getline(cin, input);
    if (!input.empty()) item->setCategory(input);

    // Update Quantity
    cout << "New quantity [" << item->getQuantity() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            item->setQuantity(stoi(input));
        } catch (...) {
            cout << "  (kept previous value)\n";
        }
    }

    // Update Reorder Level
    cout << "New reorder level [" << item->getReorderLevel() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            item->setReorderLevel(stoi(input));
        } catch (...) {
            cout << "  (kept previous value)\n";
        }
    }

    // Update Unit Price
    cout << "New unit price [$" << fixed << setprecision(2) << item->getUnitPrice() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            item->setUnitPrice(stod(input));
        } catch (...) {
            cout << "  (kept previous value)\n";
        }
    }

    saveInventory();
    cout << "\n✅ Item updated successfully!\n";
}

// UPDATE: Adjust stock quantity (IN/OUT)
void InventoryManager::performStockInOut() {
    string itemID;
    cout << "\nEnter Item ID for stock adjustment: ";
    getline(cin, itemID);

    InventoryItem* item = findItemByID(itemID);
    if (item == nullptr) {
        cout << "❌ Item not found!\n";
        return;
    }

    printHeader("STOCK IN/OUT");
    cout << "Item: " << item->getItemName() << "\n";
    cout << "Current Quantity: " << item->getQuantity() << "\n\n";

    cout << "Select operation:\n";
    cout << "  1. Stock IN (Add quantity)\n";
    cout << "  2. Stock OUT (Remove quantity)\n";
    cout << "Enter choice (1-2): ";

    string choice;
    getline(cin, choice);

    int quantity;
    cout << "Enter quantity: ";
    while (true) {
        string input;
        getline(cin, input);
        try {
            quantity = stoi(input);
            if (quantity <= 0) {
                cout << "  Error: Enter a positive number!\n";
                cout << "Enter quantity: ";
                continue;
            }
            break;
        } catch (...) {
            cout << "  Error: Invalid input!\n";
            cout << "Enter quantity: ";
        }
    }

    int newQuantity = item->getQuantity();
    string operation;

    if (choice == "1") {
        newQuantity += quantity;
        operation = "IN";
    } else if (choice == "2") {
        if (item->getQuantity() < quantity) {
            cout << "❌ Error: Cannot remove more than available stock!\n";
            return;
        }
        newQuantity -= quantity;
        operation = "OUT";
    } else {
        cout << "❌ Invalid choice!\n";
        return;
    }

    item->setQuantity(newQuantity);
    saveInventory();

    cout << "\n✅ Stock " << operation << " successful!\n";
    cout << "New Quantity: " << item->getQuantity() << "\n";
}

// DELETE: Remove item
void InventoryManager::deleteItem() {
    string searchID;
    cout << "\nEnter Item ID to delete: ";
    getline(cin, searchID);

    InventoryItem* item = findItemByID(searchID);
    if (item == nullptr) {
        cout << "❌ Item not found!\n";
        return;
    }

    cout << "\nItem Details:\n";
    cout << "  Name: " << item->getItemName() << "\n";
    cout << "  Category: " << item->getCategory() << "\n";
    cout << "  Quantity: " << item->getQuantity() << "\n";

    cout << "\nAre you sure you want to delete this item? (y/n): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y") {
        // Find and erase the item
        for (size_t i = 0; i < items.size(); i++) {
            if (toLower(items[i].getItemID()) == toLower(searchID)) {
                items.erase(items.begin() + i);
                saveInventory();
                cout << "\n✅ Item deleted successfully!\n";
                return;
            }
        }
    } else {
        cout << "❌ Deletion cancelled.\n";
    }
}
