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
    TransactionNode *getMiddle(TransactionNode *start)
    {
        if (!start)
        {
            return nullptr;
        }
        else
        {
            TransactionNode *slow = start;
            TransactionNode *fast = start->next;
            while (fast && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        }
    }

    TransactionNode *mergeSortedByLocation(TransactionNode *left, TransactionNode *right)
    {
        if (!left)
        {
            return right;
        }

        if (!right)
        {
            return left;
        }

        TransactionNode *result = nullptr;

        if (left->data.location <= right->data.location)
        {
            result = left;
            result->next = mergeSortedByLocation(left->next, right);
        }
        else
        {
            result = right;
            result->next = mergeSortedByLocation(left, right->next);
        }

        return result;
    }

    TransactionNode *mergeSortByLocationHelper(TransactionNode *node)
    {
        if (!node || !node->next)
        {
            return node;
        }
        TransactionNode *middle = getMiddle(node);
        TransactionNode *nextToMiddle = middle->next;
        middle->next = nullptr;

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
        int maxPrint = std::min(size, 300);
        while (current != nullptr && count < maxPrint)
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

    // SORTING USING MERGE SORT FOR LINKED LIST
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

    // searching using linear search
    TransactionLinkedList *linearSearch(const string &type)
    {
        TransactionLinkedList *result = new TransactionLinkedList();
        TransactionNode *current = head;

        while (current != nullptr)
        {
            if (current->data.transaction_type == type)
            {
                result->add(current->data);
            }
            current = current->next;
        }

        return result;
    }

    // searching using self-adjusting transaction type
    void moveNodeToFront(TransactionNode *prev, TransactionNode *current)
    {
        if (!prev || !current || current == head)
            return; // do nothing if current is already head or invalid

        prev->next = current->next; // remove current from its position
        current->next = head;       // point current to old head
        head = current;             // update head
    }

    TransactionLinkedList *selfAdjustSearch(const string &type)
    {
        TransactionLinkedList *result = new TransactionLinkedList();

        // // handle head separately
        // while (head && head->data.transaction_type == type)
        // {
        //     result->add(head->data);
        //     moveNodeToFront(head, nullptr); // already at front, just keep
        // }

        TransactionNode *prev = head;
        if (!prev)
            return result;

        TransactionNode *current = head->next;

        while (current)
        {
            if (current->data.transaction_type == type)
            {
                result->add(current->data);

                // move current to front
                prev->next = current->next;
                current->next = head;
                head = current;

                // start again after head change
                current = prev->next;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }

        return result;
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

    TransactionLinkedList *chooseAndSearchByTransactionType(const string &type)
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
        cout << "\nSearching transaction data of type " << type << "..." << endl;
        TransactionLinkedList *result = nullptr;
        if (searchChoice == 1)
        {
            measureAndReport("Linear search", [&]()
                             { result = linearSearch(type); });
        }
        else
        {
            measureAndReport("Self-adjusting linear search", [&]()
                             { result = selfAdjustSearch(type); });
        }
        cout << "Initial number of transaction data: " << size << endl;
        cout << "Current number of transaction data: " << result->getSize() << endl;
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
};