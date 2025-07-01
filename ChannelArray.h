#pragma once

using namespace std;
#include <string>
#include <iostream>

class TransactionTypeArray
{
private:
    string *types;
    int size;
    int capacity;

    void resize()
    {
        int newCapacity = capacity * 2;
        string *newChannels = new string[newCapacity];
        for (int i = 0; i < size; ++i)
        {
            newChannels[i] = types[i];
        }
        delete[] types;
        types = newChannels;
        capacity = newCapacity;
    }

public:
    TransactionTypeArray()
    {
        // initial capacity: 4
        types = new string[4];
        size = 0;
        capacity = 4;
    }
    bool contains(const string &val)
    {
        for (int i = 0; i < size; ++i)
            if (types[i] == val)
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
            types[size++] = val;
        }
    }
    void printOptions()
    {
        cout << "Available Payment Channels:\n"
             << endl;
        for (int i = 0; i < size; ++i)
            cout << (i + 1) << ". " << types[i] << "\n";
    }
    string get(int index)
    {
        return (index >= 0 && index < size) ? types[index] : "";
    }
    int getSize()
    {
        return size;
    }
    ~TransactionTypeArray()
    {
        delete[] types;
    }
};