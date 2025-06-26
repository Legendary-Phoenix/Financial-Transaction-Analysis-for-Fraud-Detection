#pragma once

#include <iostream>
#include "TransactionNode.h"
using namespace std;

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

    void printAll() const
    {
        TransactionNode *current = head;
        while (current != nullptr)
        {
            cout
                << current->data.transaction_id << "\n"
                << current->data.payment_channel << "\n"
                << current->data.location << "\n"
                << "----------------------------------\n"
                << endl;
            current = current->next;
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