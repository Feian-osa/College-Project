# PROJECT SCOPE: Warehouse Inventory Management System

## Executive Summary

A **modular, professional-grade C++ inventory management system** designed for educational purposes and practical warehouse operations. The system demonstrates enterprise-level software engineering practices through separation of concerns, modular architecture, and comprehensive business logic implementation.

---

## 1. Project Objectives

### Primary Goals
- Implement a complete inventory management solution with CRUD (Create, Read, Update, Delete) operations
- Demonstrate modular software architecture using separate, independent modules
- Provide real-time low stock alerts and monitoring capabilities
- Generate comprehensive business reports for inventory analysis
- Maintain a complete audit trail of all inventory transactions
- Ensure data persistence and integrity through file-based storage

### Educational Goals
- Apply object-oriented programming (OOP) principles in C++
- Practice professional code organization and documentation
- Implement design patterns (separation of concerns, factory pattern)
- Demonstrate proper error handling and user input validation
- Show best practices in C++ header/implementation separation

---

## 2. System Scope

### Functional Scope

#### 2.1 CRUD Operations (Inventory Core Module)
**User can:**
- ✅ **CREATE**: Add new inventory items with ID, name, category, quantity, reorder level, and unit price
- ✅ **READ**: View all items or search by item ID, name, or category
- ✅ **UPDATE**: Modify existing item details (quantity, price, reorder level)
- ✅ **DELETE**: Remove items from inventory
- ✅ **STOCK ADJUSTMENT**: Perform IN/OUT transactions to adjust quantities

**Data Validation:**
- Prevent duplicate item IDs
- Validate numeric inputs (quantity, price ≥ 0)
- Prevent deletion of items in active use
- Enforce non-empty item names

#### 2.2 Report Generation Module (ReportWriter)
**System generates 5 types of reports:**
1. **Complete Inventory Report** - All items with totals, values, and categories
2. **Low Stock Alert Report** - Items below reorder threshold with shortage details
3. **Inventory Value Report** - Financial analysis with cost per item and total value
4. **Category-wise Report** - Items grouped by category with subtotals
5. **Quick Summary** - Console display of key inventory metrics

**Report Features:**
- Timestamped filenames for tracking
- Professional formatting with headers and separators
- Saved to `Reports/` directory for archival
- Auto-calculated totals and statistics
- Export-ready text format

#### 2.3 Low Stock Alert System (LowStockAlert)
**Alert Capabilities:**
- ✅ Monitor items against **default threshold** (10 units)
- ✅ Check items against **custom thresholds** (user-defined)
- ✅ Classify urgency levels:
  - **CRITICAL**: Quantity ≤ 50% of reorder level
  - **OUT OF STOCK**: Quantity = 0
  - **NORMAL**: Below threshold but above critical
- ✅ Display alert summary dashboard
- ✅ Show shortage calculations (units needed to reach threshold)

**Alert Output:**
- Item ID, name, current stock, reorder level, units short
- Color-coded urgency indicators (✅ ⚠️ 🔴 ⛔)
- Action recommendations for restocking

#### 2.4 Transaction Logging & Audit Trail (TransactionLogger)
**Logging Coverage:**
- ✅ Log all CRUD operations (ADD, UPDATE, DELETE)
- ✅ Log all stock adjustments (IN, OUT)
- ✅ Capture timestamp, operator ID, item ID, quantity, reason
- ✅ Assign unique transaction IDs (TXN0001, TXN0002, etc.)
- ✅ Maintain sequence for audit purposes

**Query Capabilities:**
- View all transactions chronologically
- Filter transactions by item ID
- Filter transactions by type (ADD, UPDATE, DELETE, IN, OUT)
- Generate transaction history reports
- Export for compliance/audit purposes

### Non-Functional Scope

#### 2.5 Data Persistence
- **Inventory Storage**: `inventory.txt` (pipe-delimited format)
- **Transaction Log**: `transactions.txt` (pipe-delimited format)
- **Auto-save**: Data saved automatically after each operation
- **Auto-load**: Existing data loaded on program startup
- **Format**: Human-readable text for easy backup and review

#### 2.6 User Interface
- **Menu-driven Interface**: Hierarchical menu system
- **Main Menu**: 10 options (6 CRUD + 3 Modules + 1 Exit)
- **Submenus**: Dedicated menus for Reports, Alerts, Transactions
- **Input Validation**: All user inputs validated before processing
- **Error Messages**: Clear, actionable error messages
- **Professional Formatting**: Headers, separators, aligned columns

#### 2.7 Code Quality Standards
- **Language**: C++11 standard
- **Compiler**: GCC/G++ (MSYS2/MinGW)
- **Build**: Single-command compilation with warnings enabled
- **Comments**: Comprehensive inline documentation
- **Headers**: No namespace pollution; proper `#ifndef` guards
- **Naming**: Clear, descriptive variable and function names

---

## 3. System Architecture

### 3.1 Module Structure

```
┌─────────────────────────────────────────────────────┐
│              main.cpp (UI Layer)                     │
│  - Menu display and routing                         │
│  - User input handling                              │
│  - Module orchestration                             │
└─────────────────────────────────────────────────────┘
           ↓                ↓                ↓
    ┌──────────────┐  ┌──────────────┐  ┌──────────────┐
    │ Inventory    │  │ ReportWriter │  │ LowStockAlert│
    │ (Core)       │  │ (Reports)    │  │ (Alerts)     │
    └──────────────┘  └──────────────┘  └──────────────┘
           ↓                                    ↓
    ┌──────────────────────────────────────────────────┐
    │         TransactionLogger (Audit)                │
    │  - Logs all operations across modules            │
    └──────────────────────────────────────────────────┘
           ↓
    ┌──────────────────────────────────────────────────┐
    │    Utilities.h (Shared Helpers)                  │
    │  - Date/time functions                           │
    │  - String utilities (toLower, etc.)              │
    │  - Display utilities (headers, separators)       │
    └──────────────────────────────────────────────────┘
```

### 3.2 Class Hierarchy

**Core Classes:**
- `InventoryItem` - Represents a single inventory item
- `InventoryManager` - Manages all CRUD operations
- `ReportWriter` - Generates all report types
- `LowStockAlert` - Monitors and alerts on low stock
- `TransactionLogger` - Logs and retrieves transactions
- `Transaction` - Represents a single transaction record

---

## 4. Data Model

### 4.1 InventoryItem Structure
```
itemID          (string)   - Unique identifier (ITM001, ITM002, etc.)
itemName        (string)   - Product name
category        (string)   - Classification (Electronics, Furniture, etc.)
quantity        (int)      - Current stock count
reorderLevel    (int)      - Minimum threshold for alerts
unitPrice       (double)   - Price per unit
entryDate       (string)   - Date item was added (YYYY-MM-DD format)
```

### 4.2 Transaction Structure
```
transactionID   (string)   - Unique ID (TXN0001, TXN0002, etc.)
timestamp       (string)   - Date and time (YYYY-MM-DD HH:MM:SS)
transactionType (string)   - Operation type (ADD, UPDATE, DELETE, IN, OUT)
itemID          (string)   - Affected item ID
itemName        (string)   - Item name for easy reference
quantity        (int)      - Quantity involved in transaction
description     (string)   - Additional details/reason
```

### 4.3 Storage Format

**inventory.txt** (pipe-delimited):
```
ITM001|Mattress|Furniture|200|2025-12-04|50|120.00
ITM002|Steel Pipe|Hardware|500|2025-12-04|100|15.50
```

**transactions.txt** (pipe-delimited):
```
TXN0001|2025-12-04 14:30:45|ADD|ITM001|Mattress|200|New item added to inventory
TXN0002|2025-12-04 15:15:22|IN|ITM002|Steel Pipe|50|Restocking from supplier
```

---

## 5. Functional Requirements

### 5.1 Inventory Management
| Feature | Requirement | Status |
|---------|-------------|--------|
| Add Item | Enter ID, name, category, quantity, reorder level, price | ✅ Required |
| View Items | Display all items in formatted table with totals | ✅ Required |
| Search Items | Find by ID, name, or category (case-insensitive) | ✅ Required |
| Update Item | Modify any item field after addition | ✅ Required |
| Delete Item | Remove item from inventory | ✅ Required |
| Stock Adjust | Add/remove stock via IN/OUT transactions | ✅ Required |
| Calculate Value | Total inventory value (quantity × price) | ✅ Required |

### 5.2 Reporting
| Report Type | Data Shown | Format | Status |
|-------------|-----------|--------|--------|
| Inventory | All items, quantities, values, categories | Text file | ✅ Required |
| Low Stock | Items below threshold with shortage | Text file | ✅ Required |
| Value | Financial analysis per item | Text file | ✅ Required |
| Category | Items grouped by category | Text file | ✅ Required |
| Summary | Quick metrics to console | Console | ✅ Required |

### 5.3 Alerting
| Feature | Requirement | Status |
|---------|-------------|--------|
| Default Threshold | Check against 10-unit default | ✅ Required |
| Custom Threshold | Allow user-defined thresholds | ✅ Required |
| Urgency Classification | CRITICAL, OUT OF STOCK, NORMAL | ✅ Required |
| Alert Summary | Dashboard view with statistics | ✅ Required |

### 5.4 Audit Trail
| Feature | Requirement | Status |
|---------|-------------|--------|
| Log All Operations | Every CRUD + stock change logged | ✅ Required |
| Unique IDs | Sequential transaction IDs (TXN0001, etc.) | ✅ Required |
| Timestamps | Full date/time captured | ✅ Required |
| Query Capabilities | Filter by item, type, date | ✅ Required |
| Reports | Export transaction history | ✅ Required |

---

## 6. Non-Functional Requirements

### 6.1 Performance
- **Response Time**: All operations complete in < 1 second
- **Data Limit**: Support up to 10,000 items (file-based)
- **Scalability**: Modular design allows easy expansion
- **Storage**: Minimal footprint (< 1 MB for 1,000 items)

### 6.2 Reliability
- **Error Handling**: Graceful handling of invalid inputs
- **Data Integrity**: No data loss on abnormal termination
- **Validation**: All inputs validated before processing
- **Recovery**: Auto-load existing data on startup

### 6.3 Usability
- **Menu-driven**: Clear navigation for non-technical users
- **Input Guidance**: Prompts and examples for data entry
- **Error Messages**: Clear explanations of problems
- **Documentation**: README, guides, and quick reference included

### 6.4 Maintainability
- **Modularity**: Independent modules for easy modification
- **Documentation**: Comments explain complex logic
- **Naming**: Descriptive variable/function names
- **Structure**: Clear separation of concerns

### 6.5 Code Standards
- **Language**: C++11 compatible
- **Compilation**: Single g++ command with `-std=c++11` flag
- **Warnings**: Zero compiler warnings with `-Wall -Wextra`
- **Style**: Professional coding standards

---

## 7. Out of Scope

### Features NOT Included
- ❌ Database backend (file-based storage only)
- ❌ GUI/graphical interface (console menu-driven only)
- ❌ Network/multi-user support
- ❌ Email/SMS alerts
- ❌ Automatic reordering
- ❌ Barcode/QR code scanning
- ❌ Mobile app
- ❌ API/web service
- ❌ Advanced analytics/forecasting
- ❌ User authentication/roles
- ❌ Real-time synchronization

### Constraints
- **Single-user**: Not designed for concurrent access
- **Local storage**: No cloud sync capability
- **Manual operation**: All actions require user input
- **Text reports**: No PDF/Excel export
- **Console UI**: Terminal-based only

---

## 8. Deliverables

### 8.1 Source Code
- ✅ `main.cpp` - Main program (CRUD + menu interface)
- ✅ `Inventory.h / Inventory.cpp` - Core inventory module
- ✅ `ReportWriter.h / ReportWriter.cpp` - Reporting module
- ✅ `LowStockAlert.h / LowStockAlert.cpp` - Alert system
- ✅ `TransactionLogger.h / TransactionLogger.cpp` - Audit trail
- ✅ `Utilities.h` - Shared helper functions

### 8.2 Compiled Executable
- ✅ `inventory.exe` - Ready-to-run Windows executable

### 8.3 Documentation
- ✅ `README.md` - Complete system documentation
- ✅ `COMPILATION_GUIDE.txt` - Build instructions
- ✅ `QUICK_REFERENCE.txt` - User quick reference
- ✅ `PROJECT_SCOPE.md` - This document
- ✅ `PROJECT_COMPLETION_SUMMARY.txt` - Project status
- ✅ `FILE_INDEX.txt` - File directory
- ✅ `FINAL_VERIFICATION.txt` - Verification checklist
- ✅ `START_HERE.txt` - Getting started guide

### 8.4 Configuration
- ✅ `.vscode/c_cpp_properties.json` - VS Code IntelliSense settings
- ✅ `.vscode/tasks.json` - VS Code build tasks

### 8.5 Data Files (Generated at Runtime)
- 📁 `inventory.txt` - Persistent inventory storage
- 📁 `transactions.txt` - Persistent transaction log
- 📁 `Reports/` - Directory for generated reports

---

## 9. Use Cases

### Use Case 1: Adding New Inventory
**Actor**: Warehouse Manager  
**Flow**:
1. Select "Add New Item" from menu
2. Enter item ID (ITM003)
3. Enter item name (Widget A)
4. Enter category (Electronics)
5. Enter quantity (500)
6. Enter reorder level (50)
7. Enter unit price ($25.00)
8. System saves and logs transaction (TXN0001)

### Use Case 2: Checking Low Stock
**Actor**: Warehouse Manager  
**Flow**:
1. Select "Low Stock Alerts" from menu
2. Choose to check with default threshold (10 units)
3. System displays all items below 10 units with urgency levels
4. Manager can see which items need restocking

### Use Case 3: Generating Reports
**Actor**: Management  
**Flow**:
1. Select "Report Management" from menu
2. Choose report type (e.g., "Inventory Value Report")
3. System generates timestamped report file
4. Report saved to `Reports/InventoryValue_2025-12-04.txt`
5. Manager can download and analyze

### Use Case 4: Auditing Transactions
**Actor**: Auditor  
**Flow**:
1. Select "Transaction History" from menu
2. Choose to view all transactions
3. System displays chronological list with timestamps
4. Can filter by item ID or transaction type
5. Generate transaction report for compliance

---

## 10. Success Criteria

### Functional Success
- ✅ All CRUD operations work without errors
- ✅ Reports generate correctly with accurate calculations
- ✅ Alerts trigger for low stock items
- ✅ Transactions logged for all operations
- ✅ Data persists across program restarts

### Quality Success
- ✅ Code compiles with zero warnings
- ✅ All input validation works
- ✅ No crashes on edge cases
- ✅ Professional documentation complete
- ✅ Clear, intuitive user interface

### Delivery Success
- ✅ All source files included
- ✅ Executable builds and runs
- ✅ Documentation covers all features
- ✅ Ready for college project submission
- ✅ Demonstrates professional software engineering

---

## 11. Technical Specifications

### Build Environment
- **Language**: C++11
- **Compiler**: GCC/G++ (MSYS2/MinGW)
- **Platform**: Windows (x64)
- **IDE**: VS Code (recommended)

### Compilation
```bash
g++ -std=c++11 -Wall -Wextra -o inventory.exe \
    main.cpp Inventory.cpp ReportWriter.cpp \
    LowStockAlert.cpp TransactionLogger.cpp
```

### Execution
```bash
./inventory.exe
```

### Project Statistics
- **Total Lines of Code**: 1,400+
- **Source Files**: 6 (.cpp files)
- **Header Files**: 6 (.h files)
- **Documentation**: 8 files
- **Executable Size**: ~600 KB

---

## 12. Future Enhancement Opportunities

### Potential Extensions
- Add database backend (SQLite, MySQL)
- Implement web interface (REST API + frontend)
- Add user authentication and roles
- Email/SMS alert notifications
- Automatic reorder generation
- Advanced reporting with charts/graphs
- Mobile application
- Barcode/QR scanning
- Supplier integration
- Forecasting and demand planning

---

## 13. Conclusion

This **Warehouse Inventory Management System** is a complete, production-ready educational project that demonstrates professional C++ development practices. It provides all essential inventory management features through a clean, modular architecture with comprehensive documentation, making it ideal for college projects, portfolio demonstration, and practical warehouse use.

The system successfully balances **functionality** (5 key modules), **quality** (clean architecture, zero warnings), and **usability** (intuitive menu interface), creating a professional-grade solution for inventory tracking and management.

---

**Project Status**: ✅ **COMPLETE AND VERIFIED**  
**Last Updated**: December 4, 2025  
**Version**: 1.0

