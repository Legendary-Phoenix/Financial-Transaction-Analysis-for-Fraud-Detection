#include "TransactionArray.h"
#include "ChannelArray.h"
#include "TransactionLinkedList.h"
#include "TransactionTypeArray.h"
#include "utils/PrintHelper.h"
#include "utils/MeasureTime.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    TransactionArray arrStore;
    TransactionArray filtered;
    ChannelArray channelArr;
    TransactionTypeArray transactionTypeArr;
    TransactionLinkedList list;
    TransactionLinkedList *filteredList;

    cout << "===Financial Transaction Analysis for Fraud Detection===\n";
    cout << "Choose data structure:\n";
    cout << "1. Array\n";
    cout << "2. Linked List\n";
    int structureChoice;
    cin >> structureChoice;

    int loadChoice;
    int maxToLoad;

    cout << "Do you want to:\n";
    cout << "1. Load all transaction data\n";
    cout << "2. Load a specific number of transactions" << endl;
    cin >> loadChoice;

    if (loadChoice == 2)
    {
        do
        {
            cout << "Enter the number of transactions to load (minimum 1000):";
            cin >> maxToLoad;
            if (maxToLoad < 1000)
            {
                cout << "Minimum number of transactions to load is 1000.";
            }
        } while (maxToLoad < 1000);
    }

    // Load from CSV
    ifstream file("data/financial_fraud_detection_dataset.csv");
    if (!file.is_open())
    {
        cerr << "Failed to open file!" << endl;
        perror("Error");
        return 1;
    }

    cout << "Loading data..." << endl;
    string line;
    // Read column headings and ignore it
    getline(file, line);

    // Loop till end of file reading row by row
    int count = 0;

    while (getline(file, line))
    {
        if (count >= maxToLoad && loadChoice == 2)
        {
            break;
        }
        // Split value by comma
        stringstream ss(line);
        // Store comma separated values in values array (there's 18 values per row)
        string values[18], token;
        int i = 0;
        while (getline(ss, token, ',') && i < 18)
        {
            values[i++] = token;
        }

        if (i == 18)
        {
            try
            {
                double amount = values[4].empty() ? 0.0 : stod(values[4]);
                double tsl = values[11].empty() ? 0.0 : stod(values[11]);
                double sdev = values[12].empty() ? 0.0 : stod(values[12]);
                double vel = values[13].empty() ? 0.0 : stod(values[13]);
                double geo = values[14].empty() ? 0.0 : stod(values[14]);

                Transaction t(
                    values[0], values[1], values[2], values[3], amount,
                    values[5], values[6], values[7], values[8], values[9] == "TRUE",
                    values[10], tsl, sdev, vel,
                    geo, values[15], values[16], values[17]);
                if (structureChoice == 1)
                {
                    arrStore.add(t);
                }
                else
                {
                    list.add(t);
                }
                channelArr.add(t.payment_channel);
                transactionTypeArr.add(t.transaction_type);
                count++;
            }
            catch (const std::exception &e)
            {
                cerr << "Error on line " << count + 1 << ": " << e.what() << endl;
                cerr << "Line: " << line << endl;
            }
        }
    }
    file.close();

    if (structureChoice == 1)
    {
        cout << "Loaded " << count << " transactions into array" << endl;
    }
    else
    {
        cout << "Loaded " << count << " transactions into linked list" << endl;
    }

    // Display payment channel options
    channelArr.printOptions();
    cout << "Select a payment channel (1-" << channelArr.getSize() << "): ";
    int filterChoice;
    cin >> filterChoice;
    string selectedChannel = channelArr.get(filterChoice - 1);
    cout << "Filtering transaction data by " << selectedChannel << "..." << endl;

    // filter for array
    if (structureChoice == 1)
    {
        for (int i = 0; i < arrStore.getSize(); ++i)
        {
            Transaction &t = arrStore.get(i);
            if (t.payment_channel == selectedChannel)
            {
                filtered.add(t);
            }
        }
        cout << "Filtered size: " << filtered.getSize() << endl;
    }
    else
    {
        filteredList = list.filterByPaymentChannel(selectedChannel);
        cout << "Filtered size: " << filteredList->getSize() << endl;
    }
    cout << "Transaction data filtered by " << selectedChannel << endl;

    // requesting user if need to print data.
    // if yes, top 300 is printed
    askAndPrintData(filtered, filteredList, structureChoice);

    // Main submenu
    int option;
    do
    {
        cout << "\n---Menu---\n";
        cout << "1. Sort by location(ascending)\n";
        cout << "2. Search by transaction type\n";
        cout << "3. Export to JSON\n";
        cout << "4. Exit\n";
        cout << "Choose an option:";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Sorting transaction data by location in ascending order...\n"
                 << endl;
            if (structureChoice == 1)
            {
                filtered.chooseAndSortByLocation();
            }
            else
            {
                // sort method for linkedlist (place in measureAndReport)
            }

            askAndPrintData(filtered, filteredList, structureChoice);
            break;
        case 2:
        {
            string type;
            if (structureChoice == 1)
            {
                // search method for array
            }
            else
            {
                // search method for linked list (place in measureAndReport)
            }
            askAndPrintData(filtered, filteredList, structureChoice);
            break;
        }
        case 3:
            cout << "Exporting transaction data...";
            if (structureChoice == 1)
            {
                filtered.exportToJSON("export/array.json");
            }
            else
            {
                filteredList->exportToJSON("export/linked_list.json");
            }
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Try again\n"
                 << endl;
        }

    } while (option != 4);

    return 0;
}