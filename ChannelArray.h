#pragma once

using namespace std;
#include <string>
#include <iostream>

class ChannelArray
{
private:
    string *channels;
    int size;
    int capacity;

    void resize()
    {
        int newCapacity = capacity * 2;
        string *newChannels = new string[newCapacity];
        for (int i = 0; i < size; ++i)
        {
            newChannels[i] = channels[i];
        }
        delete[] channels;
        channels = newChannels;
        capacity = newCapacity;
    }

public:
    ChannelArray()
    {
        // initial capacity: 4
        channels = new string[4];
        size = 0;
        capacity = 4;
    }
    bool contains(const string &val)
    {
        for (int i = 0; i < size; ++i)
            if (channels[i] == val)
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
            channels[size++] = val;
        }
    }
    void printOptions()
    {
        cout << "\nAvailable Payment Channels:\n"
             << endl;
        for (int i = 0; i < size; ++i)
            cout << (i + 1) << ". " << channels[i] << "\n";
    }
    string get(int index)
    {
        return (index >= 0 && index < size) ? channels[index] : "";
    }
    int getSize()
    {
        return size;
    }
    ~ChannelArray()
    {
        delete[] channels;
    }
};