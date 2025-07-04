#pragma once

using namespace std;
#include <string>
#include <iostream>

class TransactionTypeArray
{
private:
    string *data;
    int size;
    int capacity;

    void resize()
    {
        int newCapacity = capacity * 2;
        string *newData = new string[newCapacity];
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void printOptions()
    {
        cout << "\nAvailable Transaction Types:\n"
             << endl;
        for (int i = 0; i < size; ++i)
            cout << (i + 1) << ". " << data[i] << "\n";
    }

public:
    TransactionTypeArray()
    {
        // initial capacity: 4
        data = new string[4];
        size = 0;
        capacity = 4;
    }
    bool contains(const string &val)
    {
        for (int i = 0; i < size; ++i)
            if (data[i] == val)
            {
                return true;
            }
        return false;
    }
    void add(string &val)
    {
        if (!contains(val))
        {
            if (size == capacity)
            {
                resize();
            }
            data[size++] = val;
        }
    }

    string getUserChoice()
    {
        printOptions();
        int choice;
        cout << "Enter your choice (1-" << size << "): ";
        cin >> choice;
        while (choice < 1 || choice > size)
        {
            cout << "Invalid choice. Try again: ";
            cin >> choice;
        }
        return data[choice - 1];
    }

    string get(int index)
    {
        return (index >= 0 && index < size) ? data[index] : "";
    }
    int getSize()
    {
        return size;
    }
    ~TransactionTypeArray()
    {
        delete[] data;
    }
};