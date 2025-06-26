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
        for (int i = 0; i < 300; ++i)
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