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

using namespace std;

// ===== Transaction Structure =====
// Represents a single transaction in the system

struct Transaction {
    string transactionID;      // Unique ID for this transaction
    string timestamp;          // Date and time of transaction
    string transactionType;    // Type: ADD, UPDATE, DELETE, IN, OUT
    string itemID;             // ID of affected item
    string itemName;           // Name of affected item
    int quantity;              // Quantity involved
    string description;        // Additional details
    
    // Display transaction in table format
    void display() const;
    
    // Convert to file format
    string toFileString() const;
    
    // Parse from file format
    void fromFileString(const string& data);
};


// ===== TransactionLogger Class =====
// Manages logging of all inventory transactions

class TransactionLogger {
private:
    vector<Transaction> transactions;      // All logged transactions
    string logFile;                        // Filename for persistent storage
    string nextTransactionID;              // For generating unique IDs
    
    // Helper functions
    void loadTransactions();               // Load from file
    void saveTransactions();               // Save to file
    string generateTransactionID();        // Create unique ID
    string getCurrentTimestamp() const;    // Get current time

public:
    // Constructor and Destructor
    TransactionLogger(const string& filename = "transactions.txt");
    ~TransactionLogger();
    
    // ===== Transaction Logging Methods =====
    
    // Log a transaction
    void logTransaction(const string& type, const string& itemID, 
                       const string& itemName, int quantity, 
                       const string& description);
    
    // View all transactions
    void viewAllTransactions() const;
    
    // View transactions for specific item
    void viewTransactionsForItem(const string& itemID) const;
    
    // View transactions of specific type
    void viewTransactionsByType(const string& type) const;
    
    // Generate transaction history report
    void generateTransactionReport();
    
    // ===== Getters =====
    
    // Get all transactions (for reports)
    const vector<Transaction>& getAllTransactions() const { return transactions; }
    
    // Get total transaction count
    int getTotalTransactionCount() const { return transactions.size(); }
};

#endif // TRANSACTION_LOGGER_H
