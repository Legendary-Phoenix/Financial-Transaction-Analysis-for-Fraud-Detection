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

    // START FOR MERGE SORT
    TransactionNode *getMiddle(TransactionNode* start){
        if (!start)
        {
            return nullptr;
        }else{
            TransactionNode *slow = start; 
            TransactionNode *fast = start -> next;
            while (fast && fast -> next)
            {
                slow = slow -> next;
                fast = fast -> next -> next;
            }
            return slow;
        }
    }

    TransactionNode *mergeSortedByLocation(TransactionNode *left, TransactionNode *right)
    {
        if (!left){
            return right;
        }

        if (!right){
            return left;
        }

        TransactionNode *result = nullptr;

        if (left -> data.location <= right -> data.location)
        {
            result = left;
            result -> next = mergeSortedByLocation(left -> next, right);
        }else{
            result = right;
            result -> next = mergeSortedByLocation(left, right -> next);
        }

        return result;
    }

    TransactionNode *mergeSortByLocationHelper(TransactionNode* node)
    {
        if (!node || !node -> next)
        {
            return node;
        }
        TransactionNode *middle = getMiddle(node);
        TransactionNode *nextToMiddle = middle -> next;
        middle -> next = nullptr;
        
        TransactionNode *left = mergeSortByLocationHelper(node);
        TransactionNode *right = mergeSortByLocationHelper(nextToMiddle);

        return mergeSortedByLocation(left, right);
    }
    // END MERGE SORT IN PRIVATE
public:
    TransactionLinkedList()
    {
        head = nullptr;
        size = 0;
    }

    void add(const Transaction t)
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
                << "Transaction #" << count + 1 << ":\n"
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

    TransactionLinkedList *filterByPaymentChannel(const string &channel)
    {
        TransactionLinkedList *result = new TransactionLinkedList();
        TransactionNode *current = head;

        while (current != nullptr)
        {
            if (current->data.payment_channel == channel)
            {
                result->add(current->data);
            }
            current = current->next;
        }

        return result;
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

    // SORT LINKED LIST USING BUBBLE SORT BY LOCATION
    /*void sortByLocation()
    {
        if (!head || !head -> next)
        {
            return;
        }

        bool swapped;
        do
        {
            swapped = false;
            TransactionNode *current = head;
            while (current -> next != nullptr)
            {
                if (current -> data.location > current -> next -> data.location)
                {
                    swap(current -> data, current -> next -> data);
                    swapped = true;
                }
                current = current -> next;
            }
        }while (swapped);
    }*/


    // START SORTING USING MERGE SORT FOR LINKED LIST
    void mergeSortByLocation()
    {
        head = mergeSortByLocationHelper(head);
    }


     // SORTING USING INSERTION SORT LINKED LIST BY LOCATION
    void insertionSortByLocation()
    {
        if (!head || !head->next)
        {
            return;
        }

        TransactionNode *sorted = nullptr;
        TransactionNode *current = head;

        while (current != nullptr)
        {
            TransactionNode *next = current->next;
            if (!sorted || current->data.location < sorted->data.location)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                TransactionNode *temp = sorted;
                while (temp->next && temp->next->data.location < current->data.location)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }

        head = sorted;
    }
};