/*
    Warehouse Inventory Management System
    Main.cpp - CRUD Operations and System Integration
    
    Purpose: Provides user interface for all CRUD operations and integrates
             with specialized modules (Reports, Alerts, Transaction Logging)
    
    Modules Used:
    - Inventory.h/cpp: Core CRUD operations
    - ReportWriter.h/cpp: Report generation
    - LowStockAlert.h/cpp: Low stock monitoring
    - TransactionLogger.h/cpp: Transaction logging
    - Utilities.h: Shared utility functions
*/

#include <iostream>
#include <limits>
#include "Inventory.h"
#include "ReportWriter.h"
#include "LowStockAlert.h"
#include "TransactionLogger.h"
#include "Utilities.h"

using namespace std;

// Forward declarations
void displayMainMenu();
void displayReportMenu(ReportWriter& reporter);
void displayAlertMenu(LowStockAlert& alertSystem);
void displayTransactionMenu(TransactionLogger& logger);

// ========== Main Menu Functions ==========

// Display main system menu
void displayMainMenu() {
    printSeparator(70);
    cout << "  WAREHOUSE INVENTORY MANAGEMENT SYSTEM - MAIN MENU\n";
    printSeparator(70);
    cout << "\n  ===== INVENTORY OPERATIONS (CRUD) =====\n";
    cout << "  1. Add New Item\n";
    cout << "  2. View All Items\n";
    cout << "  3. Search Items\n";
    cout << "  4. Update Item Details\n";
    cout << "  5. Adjust Stock (IN/OUT)\n";
    cout << "  6. Delete Item\n";
    cout << "\n  ===== MODULES =====\n";
    cout << "  7. Report Management\n";
    cout << "  8. Low Stock Alerts\n";
    cout << "  9. Transaction History\n";
    cout << "\n  ===== SYSTEM =====\n";
    cout << "  10. Save and Exit\n";
    printSeparator(70);
    cout << "  Enter your choice (1-10): ";
}

// Display report menu
void displayReportMenu(ReportWriter& reporter) {
    while (true) {
        printHeader("REPORT MANAGEMENT");
        cout << "\n  1. Generate Complete Inventory Report\n";
        cout << "  2. Generate Low Stock Report\n";
        cout << "  3. Generate Inventory Value Report\n";
        cout << "  4. Generate Category-wise Report\n";
        cout << "  5. Display Inventory Summary\n";
        cout << "  6. Back to Main Menu\n";
        printSeparator(70);
        cout << "  Enter your choice (1-6): ";

        string choice;
        getline(cin, choice);

        switch (choice[0]) {
            case '1':
                cout << "\n";
                reporter.generateInventoryReport();
                break;
            case '2':
                cout << "\n";
                reporter.generateLowStockReport();
                break;
            case '3':
                cout << "\n";
                reporter.generateInventoryValueReport();
                break;
            case '4':
                cout << "\n";
                reporter.generateCategoryReport();
                break;
            case '5':
                cout << "\n";
                reporter.displayInventorySummary();
                break;
            case '6':
                return;
            default:
                cout << "❌ Invalid choice! Please try again.\n";
        }

        if (choice[0] >= '1' && choice[0] <= '5') {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
}

// Display alert menu
void displayAlertMenu(LowStockAlert& alertSystem) {
    while (true) {
        printHeader("LOW STOCK ALERT SYSTEM");
        cout << "\n  1. Check Items with Default Threshold\n";
        cout << "  2. Check Items with Custom Threshold\n";
        cout << "  3. Display Alert Summary\n";
        cout << "  4. View Current Threshold\n";
        cout << "  5. Back to Main Menu\n";
        printSeparator(70);
        cout << "  Enter your choice (1-5): ";

        string choice;
        getline(cin, choice);

        switch (choice[0]) {
            case '1': {
                cout << "\n";
                alertSystem.checkLowStockItems();
                break;
            }
            case '2': {
                cout << "\nEnter custom threshold (units): ";
                string thresholdInput;
                getline(cin, thresholdInput);
                try {
                    int threshold = stoi(thresholdInput);
                    if (threshold >= 0) {
                        cout << "\n";
                        alertSystem.checkLowStockItemsWithThreshold(threshold);
                    } else {
                        cout << "❌ Threshold must be non-negative!\n";
                    }
                } catch (...) {
                    cout << "❌ Invalid input!\n";
                }
                break;
            }
            case '3':
                cout << "\n";
                alertSystem.displayAlertSummary();
                break;
            case '4':
                cout << "\nCurrent Threshold: " << alertSystem.getDefaultThreshold() << " units\n";
                break;
            case '5':
                return;
            default:
                cout << "❌ Invalid choice! Please try again.\n";
        }

        if (choice[0] >= '1' && choice[0] <= '4') {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
}

// Display transaction menu
void displayTransactionMenu(TransactionLogger& logger) {
    while (true) {
        printHeader("TRANSACTION LOGGING");
        cout << "\n  1. View All Transactions\n";
        cout << "  2. View Transactions for Specific Item\n";
        cout << "  3. View Transactions by Type\n";
        cout << "  4. Generate Transaction Report\n";
        cout << "  5. Back to Main Menu\n";
        printSeparator(70);
        cout << "  Enter your choice (1-5): ";

        string choice;
        getline(cin, choice);

        switch (choice[0]) {
            case '1': {
                cout << "\n";
                logger.viewAllTransactions();
                break;
            }
            case '2': {
                cout << "\nEnter Item ID: ";
                string itemID;
                getline(cin, itemID);
                cout << "\n";
                logger.viewTransactionsForItem(itemID);
                break;
            }
            case '3': {
                cout << "\nEnter Transaction Type (ADD/UPDATE/DELETE/IN/OUT): ";
                string type;
                getline(cin, type);
                cout << "\n";
                logger.viewTransactionsByType(type);
                break;
            }
            case '4': {
                cout << "\n";
                logger.generateTransactionReport();
                break;
            }
            case '5':
                return;
            default:
                cout << "❌ Invalid choice! Please try again.\n";
        }

        if (choice[0] >= '1' && choice[0] <= '4') {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
}

// ========== Main Function ==========

int main() {
    // Initialize all modules
    InventoryManager inventory("inventory.txt");
    ReportWriter reportWriter(inventory, "Reports/");
    LowStockAlert alertSystem(inventory, 10);  // Default threshold: 10 units
    TransactionLogger transactionLogger("transactions.txt");

    cout << "+------------------------------------------------+\n";
cout << "|   WAREHOUSE INVENTORY MANAGEMENT SYSTEM (v1.0)     |\n";
cout << "|   College Project - Well-structured Modular Design |\n";
cout << "+----------------------------------------------------+\n\n";


    cout << "System initialized successfully!\n";
    cout << "Inventory file: inventory.txt\n";
    cout << "Transaction log: transactions.txt\n";
    cout << "Reports directory: Reports/\n\n";

    int mainChoice;
    bool running = true;

    while (running) {
        displayMainMenu();
        
        string choice;
        getline(cin, choice);

        if (choice.empty()) {
            cout << "❌ No choice entered. Please try again.\n";
            continue;
        }

        // Parse the full numeric input (supports multi-digit choices like 10)
        try {
            // stoi will throw if choice isn't a valid integer
            mainChoice = stoi(choice);
        } catch (...) {
            mainChoice = -1; // invalid sentinel
        }

        switch (mainChoice) {
            // ===== CRUD Operations =====
            case 1: {
                // Add New Item
                cout << "\n";
                inventory.addNewItem();
                transactionLogger.logTransaction("ADD", "N/A", "N/A", 0, "New item added to inventory");
                break;
            }
            case 2: {
                // View All Items
                cout << "\n";
                inventory.viewAllItems();
                break;
            }
            case 3: {
                // Search Items
                cout << "\n";
                inventory.searchItem();
                break;
            }
            case 4: {
                // Update Item Details
                cout << "\n";
                inventory.updateItem();
                transactionLogger.logTransaction("UPDATE", "N/A", "N/A", 0, "Item details updated");
                break;
            }
            case 5: {
                // Adjust Stock (IN/OUT)
                cout << "\n";
                inventory.performStockInOut();
                break;
            }
            case 6: {
                // Delete Item
                cout << "\n";
                inventory.deleteItem();
                transactionLogger.logTransaction("DELETE", "N/A", "N/A", 0, "Item deleted from inventory");
                break;
            }

            // ===== Module Menus =====
            case 7: {
                // Report Management
                cout << "\n";
                displayReportMenu(reportWriter);
                break;
            }
            case 8: {
                // Low Stock Alerts
                cout << "\n";
                displayAlertMenu(alertSystem);
                break;
            }
            case 9: {
                // Transaction History
                cout << "\n";
                displayTransactionMenu(transactionLogger);
                break;
            }
            case 10: {
                // Save and Exit
                printHeader("SYSTEM SHUTDOWN");
                cout << "\n  Saving all data...\n";
                running = false;
                break;
            }
            default: {
                cout << "\n❌ Invalid choice! Please enter a number between 1 and 10.\n";
            }
        }

        if (mainChoice >= 1 && mainChoice <= 6) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

    cout << "\n  All data saved successfully!\n";
    cout << "  Thank you for using Warehouse Inventory Management System!\n";
    cout << "\n+----------------------------------------------+\n";

    return 0;
}
