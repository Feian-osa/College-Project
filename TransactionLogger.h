/*
    TransactionLogger.h
    Transaction logging system for tracking inventory changes
*/

#ifndef TRANSACTION_LOGGER_H
#define TRANSACTION_LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Utilities.h"

// Avoid `using namespace std;` in headers to prevent symbol pollution in consumers

// ===== Transaction Structure =====
// Represents a single transaction in the system

struct Transaction {
    std::string transactionID;      // Unique ID for this transaction
    std::string timestamp;          // Date and time of transaction
    std::string transactionType;    // Type: ADD, UPDATE, DELETE, IN, OUT
    std::string itemID;             // ID of affected item
    std::string itemName;           // Name of affected item
    int quantity;                   // Quantity involved
    std::string description;        // Additional details
    
    // Display transaction in table format
    void display() const;
    
    // Convert to file format
    std::string toFileString() const;
    
    // Parse from file format
    void fromFileString(const std::string& data);
};


// ===== TransactionLogger Class =====
// Manages logging of all inventory transactions

class TransactionLogger {
private:
    std::vector<Transaction> transactions;      // All logged transactions
    std::string logFile;                        // Filename for persistent storage
    std::string nextTransactionID;              // For generating unique IDs
    
    // Helper functions
    void loadTransactions();               // Load from file
    void saveTransactions();               // Save to file
    std::string generateTransactionID();        // Create unique ID
    std::string getCurrentTimestamp() const;    // Get current time

public:
    // Constructor and Destructor
    TransactionLogger(const std::string& filename = "transactions.txt");
    ~TransactionLogger();
    
    // ===== Transaction Logging Methods =====
    
    // Log a transaction
    void logTransaction(const std::string& type, const std::string& itemID, 
                       const std::string& itemName, int quantity, 
                       const std::string& description);
    
    // View all transactions
    void viewAllTransactions() const;
    
    // View transactions for specific item
    void viewTransactionsForItem(const std::string& itemID) const;
    
    // View transactions of specific type
    void viewTransactionsByType(const std::string& type) const;
    
    // Generate transaction history report
    void generateTransactionReport();
    
    // ===== Getters =====
    
    // Get all transactions (for reports)
    const std::vector<Transaction>& getAllTransactions() const { return transactions; }
    
    // Get total transaction count
    int getTotalTransactionCount() const { return transactions.size(); }
};

#endif // TRANSACTION_LOGGER_H
