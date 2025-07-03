#pragma once
#include "libs/json.hpp"
using json = nlohmann::json;
using namespace std;
// #include "Transaction.h"
#include <iostream>
#include <fstream>
#include "utils/MergeSort.h"

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
            return *this; // Self-assignment check

        delete[] data; // Free current data

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
            cout << "Current capacity is: " << capacity << endl;
            resize(); // size is doubled when full
            cout << "Capacity doubled. Current capacity: " << capacity << endl;
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
    // sorting
    void sortByLocation()
    {
        mergeSort(data, 0, size - 1);
    }

    // need to sort array by transaction type before doing binary search
    // Compare transactions based on transaction_type
    void sortByTransactionType()
    {
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                if (data[i].transaction_type > data[j].transaction_type)
                {
                    std::swap(data[i], data[j]);
                }
            }
        }
    }

    TransactionArray binarySearchByType(const std::string &tType)
    {
        TransactionArray results;

        int left = 0, right = size - 1;

        // Find the first match
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (data[mid].transaction_type == tType)
            {
                // Found one match, now collect all matches
                // Move left
                int l = mid;
                while (l >= 0 && data[l].transaction_type == tType)
                {
                    results.add(data[l]);
                    --l;
                }
                // Move right
                int r = mid + 1;
                while (r < size && data[r].transaction_type == tType)
                {
                    results.add(data[r]);
                    ++r;
                }
                results.add(data[mid]); // Add the original match
                break;
            }
            else if (data[mid].transaction_type < tType)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return results;
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