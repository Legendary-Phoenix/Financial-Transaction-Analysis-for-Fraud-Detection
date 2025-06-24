const int MAX_SIZE = 1000000;
using namespace std;
#include "Transaction.h"
#include <iostream>

class TransactionArray
{
private:
    Transaction *data;
    int size;

public:
    TransactionArray()
    {
        data = new Transaction[MAX_SIZE];
        size = 0;
        cout << "Data Memory Address: " << "Data: " << data << endl;
    }
    void add(Transaction t)
    {
        if (size < MAX_SIZE)
        {
            data[size++] = t;
        }
    }
    Transaction &get(int index)
    {
        return data[index];
    }
    int getSize()
    {
        return size;
    }
};