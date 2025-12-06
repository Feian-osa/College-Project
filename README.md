# Warehouse Inventory Management System

## Project Overview

A **comprehensive, modular C++ inventory management system** designed for a college project. The system demonstrates professional software engineering practices including clean architecture, separation of concerns, and modular design.

---

## System Architecture

### Directory Structure

```
C++ Project/
├── main.cpp                           # Main entry point - CRUD operations
├── Utilities.h                        # Shared utility functions
├── Inventory.h / Inventory.cpp        # Core inventory module
├── ReportWriter.h / ReportWriter.cpp  # Report generation module
├── LowStockAlert.h / LowStockAlert.cpp# Alert management module
├── TransactionLogger.h / TransactionLogger.cpp  # Transaction logging
├── Reports/                           # Generated reports directory
├── inventory.txt                      # Inventory data file
├── transactions.txt                   # Transaction log file
└── README.md                          # This file
```

---

## Modules Overview

### 1. **Inventory Module** (`Inventory.h/cpp`)
Core CRUD operations for inventory management.

**Classes:**
- `InventoryItem`: Represents a single inventory item
- `InventoryManager`: Manages all inventory operations

**Key Features:**
- Add new items
- View all/search items
- Update item details
- Adjust stock (IN/OUT operations)
- Delete items
- Persistent file storage

**Data Fields per Item:**
```
- itemID (string): Unique identifier (e.g., ITM001)
- itemName (string): Product name
- category (string): Category classification
- quantity (int): Current stock level
- reorderLevel (int): Minimum quantity before alert
- unitPrice (double): Price per unit
- entryDate (string): Date item was added
```

---

### 2. **Report Writer Module** (`ReportWriter.h/cpp`)
Generates comprehensive business reports.

**Classes:**
- `ReportWriter`: Handles all reporting functionality

**Report Types:**
1. **Inventory Report**: Complete item listing with totals
2. **Low Stock Report**: Items below reorder level
3. **Inventory Value Report**: Financial analysis
4. **Category Report**: Items grouped by category
5. **Quick Summary**: Console display of key metrics

**Output:**
- All reports saved to `Reports/` directory
- Timestamped filenames for tracking

---

### 3. **Low Stock Alert Module** (`LowStockAlert.h/cpp`)
Monitors inventory levels and triggers alerts.

**Classes:**
- `LowStockAlert`: Alert management system

**Features:**
- Checks stock against threshold
- Custom threshold support
- Alert urgency levels:
  - **CRITICAL**: ≤50% of reorder level
  - **OUT OF STOCK**: Quantity = 0
  - **NORMAL**: Below threshold but above critical
- Alert summary dashboard

---

### 4. **Transaction Logger Module** (`TransactionLogger.h/cpp`)
Tracks all inventory changes for audit trail.

**Classes:**
- `Transaction`: Individual transaction record
- `TransactionLogger`: Logging and retrieval system

**Transaction Types:**
- **ADD**: New item added
- **UPDATE**: Item details modified
- **DELETE**: Item removed
- **IN**: Stock received
- **OUT**: Stock shipped

**Features:**
- Unique transaction IDs (TXN0001, TXN0002, etc.)
- Full timestamp tracking
- Searchable by item or type
- Historical report generation

---

### 5. **Utilities Module** (`Utilities.h`)
Shared helper functions used across modules.

**Functions:**
- `getCurrentDate()`: Returns date in YYYY-MM-DD format
- `getCurrentDateTime()`: Returns timestamp
- `toLower()`: Case-insensitive string conversion
- `printSeparator()`: Display formatting
- `printHeader()`: Section headers

---

## Main Program (`main.cpp`)

### Menu Structure

```
MAIN MENU
├── CRUD Operations
│   ├── 1. Add New Item
│   ├── 2. View All Items
│   ├── 3. Search Items
│   ├── 4. Update Item Details
│   ├── 5. Adjust Stock (IN/OUT)
│   └── 6. Delete Item
├── Modules
│   ├── 7. Report Management
│   │   ├── Generate Inventory Report
│   │   ├── Generate Low Stock Report
│   │   ├── Generate Value Report
│   │   ├── Generate Category Report
│   │   └── Display Summary
│   ├── 8. Low Stock Alerts
│   │   ├── Check with Default Threshold
│   │   ├── Check with Custom Threshold
│   │   ├── Display Alert Summary
│   │   └── View Current Threshold
│   └── 9. Transaction History
│       ├── View All Transactions
│       ├── View Item Transactions
│       ├── View Type Transactions
│       └── Generate Report
└── 10. Save and Exit
```

---

## Data Persistence

### Files Generated

1. **inventory.txt**
   - Stores all inventory items
   - Pipe-delimited format: `ID|Name|Category|Qty|Date|ReorderLevel|Price`
   - Auto-loaded on startup
   - Auto-saved on exit or after modifications

2. **transactions.txt**
   - Audit trail of all operations
   - Format: `TxnID|Timestamp|Type|ItemID|Name|Qty|Description`
   - Sequential transaction numbering

3. **Reports/** (Directory)
   - Timestamped report files
   - Format: `ReportType_YYYY-MM-DD.txt`

---

## Compilation & Execution

### Prerequisites
- C++11 or later
- GCC compiler (or compatible C++ compiler)
- Standard libraries (iostream, fstream, vector, etc.)

### Compilation

```bash
# Using GCC
g++ -std=c++11 -o inventory main.cpp Inventory.cpp ReportWriter.cpp LowStockAlert.cpp TransactionLogger.cpp

# Or compile individually and link
g++ -c Inventory.cpp
g++ -c ReportWriter.cpp
g++ -c LowStockAlert.cpp
g++ -c TransactionLogger.cpp
g++ -o inventory main.cpp Inventory.o ReportWriter.o LowStockAlert.o TransactionLogger.o
```

### Execution

```bash
./inventory
```

---

## Code Design Principles

### 1. **Separation of Concerns**
Each module handles one responsibility:
- Inventory: Data management
- Reports: Analysis and reporting
- Alerts: Monitoring
- Transactions: Audit logging

### 2. **Encapsulation**
- Private data members and helper methods
- Public interface for external access
- No global variables

### 3. **Reusability**
- Utility functions in separate header
- Constant references to InventoryManager
- Modular class design

### 4. **Maintainability**
- Clear, descriptive names
- Extensive comments
- Organized file structure
- Consistent formatting

### 5. **Error Handling**
- Input validation
- File I/O error checking
- Graceful error messages
- User-friendly feedback

---

## Usage Examples

### Adding an Item
```
Menu Choice: 1 (Add New Item)
Enter Item ID: ITM001
Enter Item Name: Steel Pipe
Enter Category: Hardware
Enter Quantity: 100
Enter Reorder Level: 20
Enter Unit Price: 15.50
```

### Generating Reports
```
Menu Choice: 7 (Report Management)
Submenu: 1 (Generate Inventory Report)
→ Creates file: Reports/Inventory_Report_2025-12-04.txt
```

### Checking Low Stock
```
Menu Choice: 8 (Low Stock Alerts)
Submenu: 1 (Check with Default Threshold)
→ Displays items with qty ≤ 10 units
```

### Viewing Transaction History
```
Menu Choice: 9 (Transaction History)
Submenu: 1 (View All Transactions)
→ Lists all logged operations with timestamps
```

---

## Key Features

✅ **Full CRUD Operations** - Create, Read, Update, Delete items  
✅ **Advanced Search** - Find by ID, name, or category  
✅ **Stock Management** - Adjust quantities with IN/OUT tracking  
✅ **Comprehensive Reports** - Multiple report types  
✅ **Alert System** - Low stock notifications with urgency levels  
✅ **Transaction Logging** - Complete audit trail  
✅ **Persistent Storage** - Data saved across sessions  
✅ **User-Friendly Interface** - Clear menus and feedback  
✅ **Professional Code** - Well-commented and organized  
✅ **College-Ready** - Educational design patterns  

---

## Class Diagram Summary

```
┌─────────────────────────────────────────────────────────────┐
│                   InventoryManager (CORE)                   │
│  ┌────────────────────────────────────────────────────────┐ │
│  │ - items: vector<InventoryItem>                         │ │
│  │ + addNewItem() / viewAllItems() / searchItem()         │ │
│  │ + updateItem() / performStockInOut() / deleteItem()    │ │
│  │ + getAllItems() / getTotalItemsCount()                 │ │
│  └────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
         ▲                    ▲                    ▲
         │                    │                    │
         │                    │                    │
    ┌────┴─────┐      ┌──────┴────┐      ┌────────┴──────┐
    │ Report   │      │ LowStock  │      │ Transaction  │
    │ Writer   │      │ Alert     │      │ Logger       │
    └──────────┘      └───────────┘      └──────────────┘
```

---

## Future Enhancement Ideas

1. Database integration (SQLite/MySQL)
2. GUI implementation (Qt/wxWidgets)
3. Email notifications for alerts
4. Advanced analytics and forecasting
5. Barcode/QR code scanning
6. Multi-user support with authentication
7. Real-time price updates
8. Supplier management
9. Export to Excel/CSV
10. Mobile app interface

---

## Testing Checklist

- [ ] Add 5+ items successfully
- [ ] Search items by different criteria
- [ ] Update item quantities and details
- [ ] Generate all 5 report types
- [ ] Verify transaction logging
- [ ] Test low stock alerts
- [ ] Check file persistence
- [ ] Verify data loads on restart
- [ ] Test input validation
- [ ] Verify calculations (totals, values)

---

## VS Code Configuration Guide

### Recommended Settings for IntelliSense & Compilation

To avoid red warnings and ensure VS Code IntelliSense matches your actual compiler, follow these steps:

#### 1. **Update `.vscode/c_cpp_properties.json`** ✅ (Already Configured)

Your project is configured to use **GCC/G++ (MSYS2)** with **C++11 standard**.

**Current Configuration:**
- **Compiler Path**: `C:\msys64\ucrt64\bin\g++.exe`
- **C++ Standard**: `c++11`
- **IntelliSense Mode**: `gcc-x64`

If you need to verify or adjust:
1. Open `.vscode/c_cpp_properties.json`
2. Confirm the `compilerPath` points to your g++ executable
3. Ensure `cppStandard` is set to `c++11`
4. Use `intelliSenseMode` as `gcc-x64`

#### 2. **Reset IntelliSense (If Warnings Persist)**

After updating `c_cpp_properties.json`:
1. Open **Command Palette** (Ctrl+Shift+P)
2. Run: **C/C++: Reset IntelliSense Database**
3. Run: **Developer: Reload Window**

#### 3. **Header File Best Practices** (Already Applied)

All header files in this project follow these practices:
- ✅ No `using namespace std;` in headers
- ✅ All std types fully qualified with `std::`
- ✅ Proper `#include` guards (`#ifndef`, `#define`, `#endif`)
- ✅ No circular dependencies

This prevents:
- Symbol pollution across translation units
- IntelliSense parse errors
- Multiple-definition linker errors
- IDE warning squiggles

#### 4. **If You See Warnings After Setup**

**Common IntelliSense Issues & Fixes:**

| Issue | Cause | Fix |
|-------|-------|-----|
| Red squiggles on `std::` types | IntelliSense using wrong C++ standard | Update `cppStandard` in `c_cpp_properties.json` to `c++11` |
| "Cannot open include file" | IntelliSense path mismatch | Verify `includePath` includes `${workspaceFolder}/**` |
| Missing symbols after header changes | Stale IntelliSense cache | Run "C/C++: Reset IntelliSense Database" |
| Wrong compiler detected | Multiple compilers installed | Verify `compilerPath` points to correct g++ |

#### 5. **Compilation Command (Verified)**

This command works correctly with your project:

```bash
g++ -std=c++11 -Wall -Wextra -o inventory.exe main.cpp Inventory.cpp ReportWriter.cpp LowStockAlert.cpp TransactionLogger.cpp
```

- Compiles without errors or warnings ✅
- Uses C++11 standard (matches IntelliSense setting)
- Enables all warnings for code quality

---

## Troubleshooting

**Issue**: Compilation errors with old C++ standard
- **Solution**: Use `-std=c++11` or later flag

**Issue**: Reports directory not created
- **Solution**: Create `Reports/` folder manually or modify code to auto-create

**Issue**: Data not persisting
- **Solution**: Ensure write permissions in project directory

**Issue**: Search returning no results
- **Solution**: Check exact spelling; search is case-insensitive

---

## Author Notes

This system was designed to demonstrate:
- Professional C++ programming practices
- Object-oriented design principles
- Modular architecture
- File I/O operations
- Menu-driven user interfaces
- Data structures and containers
- Error handling strategies
- Documentation best practices

Perfect for college projects, learning C++, or portfolio demonstration!

---

## License & Usage

**Educational Use** - This code is provided as a college project template and learning resource.

---

**Happy Coding! 🚀**
