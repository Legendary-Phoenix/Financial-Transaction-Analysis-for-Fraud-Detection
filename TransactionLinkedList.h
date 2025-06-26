#pragma once

#include <iostream>
#include <fstream>
#include "TransactionNode.h"
#include "libs/json.hpp"
using namespace std;
using json = nlohmann::json;

class TransactionLinkedList
{
private:
    TransactionNode *head;
    int size;

public:
    TransactionLinkedList()
    {
        head = nullptr;
        size = 0;
    }

    void add(Transaction t)
    {
        TransactionNode *newNode = new TransactionNode(t);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            TransactionNode *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    int getSize() const
    {
        return size;
    }

    void exportToJSON(const string &filename) const
    {
        json j_array = json::array();

        TransactionNode *current = head;
        while (current != nullptr)
        {
            const Transaction &t = current->data;

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
            current = current->next;
        }

        ofstream file(filename);
        if (file.is_open())
        {
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
        TransactionNode *current = head;
        int count = 0;
        while (current != nullptr && count < 300)
        {

            cout
                << "Transaction ID: " << current->data.transaction_id << "\n"
                << "Payment Channel: " << current->data.payment_channel << "\n"
                << "Location: " << current->data.location << "\n"
                << "Timestamp: " << current->data.timestamp << "\n"
                << "Sender:" << current->data.sender_account << "\n"
                << "Receiver:" << current->data.receiver_account << "\n"
                << "Amount: $" << current->data.amount << "\n"
                << "Type: " << current->data.transaction_type << "\n"
                << "Merchant Category: " << current->data.merchant_category << "\n"
                << "----------------------------------\n"
                << endl;
            current = current->next;
            count++;
        }
    }

    TransactionNode *getHead() const
    {
        return head;
    }

    ~TransactionLinkedList()
    {
        TransactionNode *current = head;
        while (current != nullptr)
        {
            TransactionNode *next = current->next;
            delete current;
            current = next;
        }
    }

    TransactionLinkedList filterByPaymentChannel(string &channel)
    {
        TransactionLinkedList result;
        TransactionNode *current = head;

        while (current != nullptr)
        {
            if (current->data.payment_channel == channel)
            {
                result.add(current->data);
            }
            current = current->next;
        }

        return result;
    }
};