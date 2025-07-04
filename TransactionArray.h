#pragma once
#include "libs/json.hpp"
using json = nlohmann::json;
using namespace std;
// #include "Transaction.h"
#include <iostream>
#include <fstream>
#include "utils/MergeSort.h"
#include "utils/MeasureTime.h"

class TransactionArray
{
private:
    Transaction *data;
    int capacity;
    int size;

    void resize()
    {
        int newCapacity = capacity * 2;
        Transaction *newData = new Transaction[newCapacity];
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    TransactionArray()
    {
        // create custom array with initial size of 10
        data = new Transaction[10];
        capacity = 10;
        size = 0;
        // cout << "Data Memory Address: " << "Data: " << data << endl;
    }

    TransactionArray &operator=(const TransactionArray &other)
    {
        if (this == &other)
            return *this; // self-assignment check

        delete[] data;

        capacity = other.capacity;
        size = other.size;
        data = new Transaction[capacity];
        for (int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }

        return *this;
    }

    void add(Transaction t)
    {
        if (size == capacity)
        {
            // cout << "Current capacity is: " << capacity << endl;
            resize(); // size is doubled when full
            // cout << "Capacity doubled. Current capacity: " << capacity << endl;
        }
        data[size++] = t;
    }
    Transaction &get(int index)
    {
        return data[index];
    }
    int getSize()
    {
        return size;
    }
    ~TransactionArray()
    {
        delete[] data;
    }
    // merge sort
    void mergeSortByLocation()
    {
        mergeSort(data, 0, size - 1);
    }
    // insertion sort
    void insertionSortByLocation()
    {
        for (int i = 1; i < size; ++i)
        {
            Transaction key = data[i];
            int j = i - 1;

            // move elements greater than key to one position ahead
            while (j >= 0 && data[j].location > key.location)
            {
                data[j + 1] = data[j];
                j--;
            }

            data[j + 1] = key;
        }
    }

    // search using linear search

    void linearSearch(const string &tType)
    {
        int transactionDataSize = 0;
        for (int i = 0; i < size; i++)
        {
            if (data[i].transaction_type == tType)
            {
                // rewriting the TransactionArray entirely
                data[transactionDataSize] = data[i];
                transactionDataSize++;
            }
        }
        size = transactionDataSize;
    }

    // search using self-adjusting linear search
    void selfAdjustingLinearSearch(const string &tType)
    {
        bool found = false;
        int write = 0;

        for (int i = 0; i < size; ++i)
        {
            if (data[i].transaction_type == tType)
            {
                found = true;
                // rewriting the array
                data[write] = data[i];
                // Move-to-front within filtered portion
                if (write > 0)
                {
                    Transaction temp = data[write];
                    data[write] = data[write - 1];
                    data[write - 1] = temp;
                }
                write++;
            }
        }
        size = write;

        if (!found)
        {
            cout << "No transactions of type '" << tType << "' found.\n";
        }
    }

    void chooseAndSortByLocation()
    {
        int sortChoice;
        do
        {
            cout << "\nChoose a sorting method:\n";
            cout << "1. Merge Sort\n";
            cout << "2. Insertion Sort\n";
            cout << "Enter choice: ";
            cin >> sortChoice;

            if (sortChoice != 1 && sortChoice != 2)
            {
                cout << "Invalid sorting option.\n";
            }

        } while (sortChoice != 1 && sortChoice != 2);

        cout << "\nSorting transaction data by location in ascending order..." << endl;
        if (sortChoice == 1)
        {
            measureAndReport("Merge sort", [&]()
                             { mergeSortByLocation(); });
        }
        else
        {
            measureAndReport("Insertion sort", [&]()
                             { insertionSortByLocation(); });
        }
    }

    void chooseAndSearchByTransactionType(const string &type)
    {
        int searchChoice;
        do
        {
            cout << "\nChoose a searching method:\n";
            cout << "1. Linear Search\n";
            cout << "2. Self-Adjusting Linear Search\n";
            cout << "Enter choice: ";
            cin >> searchChoice;

            if (searchChoice != 1 && searchChoice != 2)
            {
                cout << "Invalid searching option.\n";
            }

        } while (searchChoice != 1 && searchChoice != 2);
        int initialSize = size;
        cout << "\nSearching transaction data of type " << type << "..." << endl;

        if (searchChoice == 1)
        {
            measureAndReport("Linear search", [&]()
                             { linearSearch(type); });
        }
        else
        {
            measureAndReport("Self-adjusting linear search", [&]()
                             { selfAdjustingLinearSearch(type); });
        }
        cout << "Initial number of transaction data: " << initialSize << endl;
        cout << "Current number of transaction data: " << size << endl;
    }

    void exportToJSON(const string &filename) const
    {
        json j_array = json::array();

        for (int i = 0; i < size; ++i)
        {
            const Transaction &t = data[i];
            json j = {
                {"transaction_id", t.transaction_id},
                {"timestamp", t.timestamp},
                {"sender_account", t.sender_account},
                {"receiver_account", t.receiver_account},
                {"amount", t.amount},
                {"transaction_type", t.transaction_type},
                {"merchant_category", t.merchant_category},
                {"location", t.location},
                {"device_used", t.device_used},
                {"is_fraud", t.is_fraud},
                {"fraud_type", t.fraud_type},
                {"time_since_last_transaction", t.time_since_last_transaction},
                {"spending_deviation_score", t.spending_deviation_score},
                {"velocity_score", t.velocity_score},
                {"geo_anomaly_score", t.geo_anomaly_score},
                {"payment_channel", t.payment_channel},
                {"ip_address", t.ip_address},
                {"device_hash", t.device_hash}};

            j_array.push_back(j);
        }
        ofstream file(filename);
        if (file.is_open())
        {
            // pretty print with indent of 4
            file << j_array.dump(4);
            file.close();
            cout << "Data exported to JSON file" << endl;
        }
        else
        {
            cerr << "Failed to open " << filename << "\n";
        }
    }

    void printAll() const
    {
        int count = std::min(size, 300);
        for (int i = 0; i < count; ++i)
        {
            printTransaction(data[i], i);
        }
    }
    void printTransaction(const Transaction &t, int index = -1) const
    {
        if (index >= 0)
        {
            cout << "Transaction #" << index + 1 << ":\n";
        }
        cout
            << "ID: " << t.transaction_id << "\n"
            << "Location: " << t.location << "\n"
            << "Payment Channel: " << t.payment_channel << "\n"
            << "Timestamp: " << t.timestamp << "\n"
            << "Sender:" << t.sender_account << "\n"
            << "Receiver:" << t.receiver_account << "\n"
            << "Amount: $" << t.amount << "\n"
            << "Type: " << t.transaction_type << "\n"
            << "Merchant Category: " << t.merchant_category << "\n"

            // << "  Device Used: " << t.device_used << "\n"
            // << "  Is Fraud: " << (t.is_fraud ? "Yes" : "No") << "\n"
            // << "  Fraud Type: " << t.fraud_type << "\n"
            // << "  Time Since Last: " << t.time_since_last_transaction << "\n"
            // << "  Spending Deviation Score: " << t.spending_deviation_score << "\n"
            // << "  Velocity Score: " << t.velocity_score << "\n"
            // << "  Geo Anomaly Score: " << t.geo_anomaly_score << "\n"

            // << "  IP Address: " << t.ip_address << "\n"
            // << "  Device Hash: " << t.device_hash << "\n"
            << "----------------------------------\n";
    }
};