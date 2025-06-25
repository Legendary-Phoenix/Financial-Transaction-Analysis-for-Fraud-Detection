const int MAX_SIZE = 300;
using namespace std;
// #include "Transaction.h"
#include <iostream>
#include "utils/MergeSort.cpp"

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
    // sorting
    void sortByLocation()
    {
        mergeSort(data, 0, size - 1);
    }
    void printAll()
    {
        for (int i = 0; i < size; ++i)
        {
            printTransaction(data[i], i);
        }
    }
    void printTransaction(const Transaction &t, int index = -1)
    {
        if (index >= 0)
        {
            cout << "Transaction #" << index + 1 << ":\n";
        }
        cout << "ID: " << t.transaction_id << "\n"
             << "Tiemstamp: " << t.timestamp << "\n"
             << "Sender:" << t.sender_account << "\n"
             << "Receiver:" << t.receiver_account << "\n"
             << "  Amount: $" << t.amount << "\n"
             << "  Type: " << t.transaction_type << "\n"
             << "  Merchant Category: " << t.merchant_category << "\n"
             << "  Location: " << t.location << "\n"
             << "  Device Used: " << t.device_used << "\n"
             << "  Is Fraud: " << (t.is_fraud ? "Yes" : "No") << "\n"
             << "  Fraud Type: " << t.fraud_type << "\n"
             << "  Time Since Last: " << t.time_since_last_transaction << "\n"
             << "  Spending Deviation Score: " << t.spending_deviation_score << "\n"
             << "  Velocity Score: " << t.velocity_score << "\n"
             << "  Geo Anomaly Score: " << t.geo_anomaly_score << "\n"
             << "  Payment Channel: " << t.payment_channel << "\n"
             << "  IP Address: " << t.ip_address << "\n"
             << "  Device Hash: " << t.device_hash << "\n"
             << "----------------------------------\n";
    }
};