/*
    TransactionLogger.cpp
    Implementation of Transaction Logging module
*/

#include "TransactionLogger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ========== Transaction Implementation ==========

// Display transaction in table format
void Transaction::display() const {
    cout << left << setw(12) << transactionID
         << setw(12) << transactionType
         << setw(12) << itemID
         << setw(25) << (itemName.length() > 24 ? itemName.substr(0, 21) + "..." : itemName)
         << setw(8) << quantity
         << setw(20) << timestamp
         << description << "\n";
}

// Convert transaction to file format
string Transaction::toFileString() const {
    stringstream ss;
    ss << transactionID << "|" << timestamp << "|" << transactionType << "|"
       << itemID << "|" << itemName << "|" << quantity << "|" << description;
    return ss.str();
}

// Parse transaction from file format
void Transaction::fromFileString(const string& data) {
    stringstream ss(data);
    string temp;

    getline(ss, transactionID, '|');
    getline(ss, timestamp, '|');
    getline(ss, transactionType, '|');
    getline(ss, itemID, '|');
    getline(ss, itemName, '|');
    
    getline(ss, temp, '|');
    quantity = stoi(temp);
    
    getline(ss, description);
}


// ========== TransactionLogger Implementation ==========

// Constructor - Load existing transactions
TransactionLogger::TransactionLogger(const string& filename)
    : logFile(filename), nextTransactionID("TXN0001") {
    loadTransactions();
}

// Destructor - Save transactions
TransactionLogger::~TransactionLogger() {
    saveTransactions();
}

// Load transactions from file
void TransactionLogger::loadTransactions() {
    transactions.clear();
    ifstream file(logFile);
    if (!file.is_open()) {
        // File doesn't exist yet - this is OK
        return;
    }

    string line;
    int maxTxnNum = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                Transaction txn;
                txn.fromFileString(line);
                transactions.push_back(txn);
                
                // Extract transaction number for ID generation
                string numPart = txn.transactionID.substr(3); // Remove "TXN"
                int txnNum = stoi(numPart);
                maxTxnNum = max(maxTxnNum, txnNum);
            } catch (const exception& e) {
                cerr << "Warning: Error reading transaction: " << line << endl;
            }
        }
    }
    file.close();

    // Set next ID
    stringstream ss;
    ss << "TXN" << setfill('0') << setw(4) << (maxTxnNum + 1);
    nextTransactionID = ss.str();
}

// Save transactions to file
void TransactionLogger::saveTransactions() {
    ofstream file(logFile);
    if (!file.is_open()) {
        cerr << "Error: Could not save transactions to " << logFile << "!\n";
        return;
    }

    for (const auto& txn : transactions) {
        file << txn.toFileString() << "\n";
    }
    file.close();
}

// Generate unique transaction ID
string TransactionLogger::generateTransactionID() {
    string currentID = nextTransactionID;
    
    // Increment ID for next transaction
    string numPart = nextTransactionID.substr(3);
    int txnNum = stoi(numPart) + 1;
    
    stringstream ss;
    ss << "TXN" << setfill('0') << setw(4) << txnNum;
    nextTransactionID = ss.str();
    
    return currentID;
}

// Get current timestamp
string TransactionLogger::getCurrentTimestamp() const {
    return getCurrentDateTime();
}

// Log a transaction
void TransactionLogger::logTransaction(const string& type, const string& itemID,
                                       const string& itemName, int quantity,
                                       const string& description) {
    Transaction txn;
    txn.transactionID = generateTransactionID();
    txn.timestamp = getCurrentTimestamp();
    txn.transactionType = type;
    txn.itemID = itemID;
    txn.itemName = itemName;
    txn.quantity = quantity;
    txn.description = description;

    transactions.push_back(txn);
    saveTransactions();
}

// View all transactions
void TransactionLogger::viewAllTransactions() const {
    printHeader("TRANSACTION HISTORY");

    if (transactions.empty()) {
        cout << "No transactions logged.\n";
        return;
    }

    cout << "\nTotal Transactions: " << transactions.size() << "\n\n";

    cout << left << setw(12) << "Txn ID"
         << setw(12) << "Type"
         << setw(12) << "Item ID"
         << setw(25) << "Item Name"
         << setw(8) << "Qty"
         << setw(20) << "Timestamp"
         << "Description\n";
    cout << string(119, '-') << "\n";

    for (const auto& txn : transactions) {
        txn.display();
    }
}

// View transactions for specific item
void TransactionLogger::viewTransactionsForItem(const string& itemID) const {
    printHeader("TRANSACTION HISTORY FOR ITEM");

    vector<Transaction> itemTxns;
    string searchID = toLower(itemID);

    for (const auto& txn : transactions) {
        if (toLower(txn.itemID) == searchID) {
            itemTxns.push_back(txn);
        }
    }

    if (itemTxns.empty()) {
        cout << "No transactions found for item: " << itemID << "\n";
        return;
    }

    cout << "\nItem ID: " << itemID << "\n";
    cout << "Total Transactions: " << itemTxns.size() << "\n\n";

    cout << left << setw(12) << "Txn ID"
         << setw(12) << "Type"
         << setw(8) << "Qty"
         << setw(20) << "Timestamp"
         << "Description\n";
    cout << string(80, '-') << "\n";

    for (const auto& txn : itemTxns) {
        cout << left << setw(12) << txn.transactionID
             << setw(12) << txn.transactionType
             << setw(8) << txn.quantity
             << setw(20) << txn.timestamp
             << txn.description << "\n";
    }
}

// View transactions by type
void TransactionLogger::viewTransactionsByType(const string& type) const {
    printHeader("TRANSACTIONS BY TYPE");

    vector<Transaction> typeTxns;
    string searchType = toLower(type);

    for (const auto& txn : transactions) {
        if (toLower(txn.transactionType) == searchType) {
            typeTxns.push_back(txn);
        }
    }

    if (typeTxns.empty()) {
        cout << "No transactions found of type: " << type << "\n";
        return;
    }

    cout << "\nTransaction Type: " << type << "\n";
    cout << "Total Transactions: " << typeTxns.size() << "\n\n";

    cout << left << setw(12) << "Txn ID"
         << setw(12) << "Item ID"
         << setw(25) << "Item Name"
         << setw(8) << "Qty"
         << setw(20) << "Timestamp"
         << "Description\n";
    cout << string(104, '-') << "\n";

    for (const auto& txn : typeTxns) {
        cout << left << setw(12) << txn.transactionID
             << setw(12) << txn.itemID
             << setw(25) << (txn.itemName.length() > 24 ? 
                           txn.itemName.substr(0, 21) + "..." : txn.itemName)
             << setw(8) << txn.quantity
             << setw(20) << txn.timestamp
             << txn.description << "\n";
    }
}

// Generate transaction history report
void TransactionLogger::generateTransactionReport() {
    printHeader("GENERATING TRANSACTION REPORT");

    if (transactions.empty()) {
        cout << "No transactions to report.\n";
        return;
    }

    string filename = "Reports/TransactionHistory_" + getCurrentDate() + ".txt";
    ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file: " << filename << "\n";
        return;
    }

    // Write report header
    reportFile << "=" << string(128, '=') << "\n";
    reportFile << "  TRANSACTION HISTORY REPORT\n";
    reportFile << "  Generated: " << getCurrentDateTime() << "\n";
    reportFile << "=" << string(128, '=') << "\n\n";

    // Summary statistics
    int addCount = 0, updateCount = 0, deleteCount = 0, inCount = 0, outCount = 0;

    for (const auto& txn : transactions) {
        if (txn.transactionType == "ADD") addCount++;
        else if (txn.transactionType == "UPDATE") updateCount++;
        else if (txn.transactionType == "DELETE") deleteCount++;
        else if (txn.transactionType == "IN") inCount++;
        else if (txn.transactionType == "OUT") outCount++;
    }

    reportFile << "SUMMARY:\n";
    reportFile << "  Total Transactions: " << transactions.size() << "\n";
    reportFile << "  ADD Operations: " << addCount << "\n";
    reportFile << "  UPDATE Operations: " << updateCount << "\n";
    reportFile << "  DELETE Operations: " << deleteCount << "\n";
    reportFile << "  STOCK IN Operations: " << inCount << "\n";
    reportFile << "  STOCK OUT Operations: " << outCount << "\n";
    reportFile << "\n" << string(128, '-') << "\n\n";

    // Detailed transaction list
    reportFile << left << setw(12) << "Txn ID"
               << setw(12) << "Type"
               << setw(12) << "Item ID"
               << setw(25) << "Item Name"
               << setw(8) << "Qty"
               << setw(20) << "Timestamp"
               << "Description\n";
    reportFile << string(119, '-') << "\n";

    for (const auto& txn : transactions) {
        reportFile << left << setw(12) << txn.transactionID
                   << setw(12) << txn.transactionType
                   << setw(12) << txn.itemID
                   << setw(25) << (txn.itemName.length() > 24 ? 
                                 txn.itemName.substr(0, 21) + "..." : txn.itemName)
                   << setw(8) << txn.quantity
                   << setw(20) << txn.timestamp
                   << txn.description << "\n";
    }

    reportFile << "\n" << "=" << string(128, '=') << "\n";

    reportFile.close();

    cout << "\n✅ Transaction Report generated: " << filename << "\n";
    cout << "   Total Transactions: " << transactions.size() << "\n";
}
