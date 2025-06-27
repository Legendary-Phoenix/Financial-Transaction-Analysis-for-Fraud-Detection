#include "TransactionArray.h"
#include "TransactionDLL.h"
#include "loaders.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "json.hpp"
#include <string>
<<<<<<< Updated upstream
#include <set>
#include <iomanip>
=======
#include <filesystem>
>>>>>>> Stashed changes
using namespace std;
using json = nlohmann::json;

void exportToJson(TransactionDLL& dll, const string& filename, const string& filterChannel){
    json j;
    Node* current = dll.getHead();

    while (current){
        if(current -> data.payment_channel == filterChannel){
            j.push_back({
                {"transaction_id", current->data.transaction_id},
                {"timestamp", current->data.timestamp},
                {"sender_account", current->data.sender_account},
                {"receiver_account", current->data.receiver_account},
                {"amount", current->data.amount},
                {"transaction_type", current->data.transaction_type},
                {"merchant_category", current->data.merchant_category},
                {"location", current->data.location},
                {"device_used", current->data.device_used},
                {"is_fraud", current->data.is_fraud},
                {"fraud_type", current->data.fraud_type},
                {"time_since_last_transaction", current->data.time_since_last_transaction},
                {"spending_deviation_score", current->data.spending_deviation_score},
                {"velocity_score", current->data.velocity_score},
                {"geo_anomaly_score", current->data.geo_anomaly_score},
                {"payment_channel", current->data.payment_channel},
                {"ip_address", current->data.ip_address},
                {"device_hash", current->data.device_hash}
            });
        }
        current = current -> next;
    }

    ofstream out(filename);
    if (out.is_open()) {
        out << setw(4) << j;
        cout << "Exported to " << filename << endl;
    }else{
        cerr << "Failed to open file for writing. " << endl;
    }
}



int main()
{
    string filename = "data/financial_fraud_detection_dataset.csv";



    int choice;
    cout << "Select Data Structure to use: \n1. Array\n2. Doubly Linked List\nEnter choice: ";
    cin >> choice;
    cin.ignore();
   

    if(choice == 1){

        TransactionArray arrStore;

        // Load from CSV
        ifstream file("data/financial_fraud_detection_dataset.csv");
        if (!file.is_open())
        {
            cerr << "Failed to open file!" << endl;
            perror("Error");
            return 1;
        }
        cout << "I reach here:" << endl;
        string line;
        // Read column headings and ignore it
        getline(file, line);

        // Loop till end of file reading row by row
        int count = 0;

        while (getline(file, line) && count < 300)
        {
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
                    arrStore.add(t);
                    count++;
                }
                catch (const std::exception &e)
                {
                    cerr << "⚠️ Error on line " << count + 1 << ": " << e.what() << endl;
                    cerr << "Line: " << line << endl;
                }
            }
        }
        file.close();
        cout << "Loaded " << count << " transactions into array" << endl;
        arrStore.sortByLocation();
        arrStore.printAll();
        cout << "Exit?: ";
        int exit;
        cin >> exit; 
    }else if (choice == 2){
        TransactionDLL dllStore;
        loadDataIntoDLL(dllStore, filename);

        int option;
        do{
            cout << "\nDoubly Linked List Menu:" << endl;
            cout << "1. Display by Payment Channel" << endl;
            cout << "2. Sort by location (ascending)" << endl;
            cout << "3. Search by transaction type" << endl;
            cout << "4. Export to JSON by payment channel" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter Your Option: ";
            cin >> option;
            cin.ignore();
            switch (option){
                case 1:
                    dllStore.displayAllByPaymentChannel();
                    break;
                case 2:
                    dllStore.sortByLocation();
                    dllStore.printAll();
                    break;
                case 3:{
                    string type;
                    cout << "Enter payment channel to export: ";
                    getline(cin, type);
                    exportToJson(dllStore, "exported_data.json", type);
                    break;
                }
                case 4: {
                    string channel;
                    cout << "Enter payment channel to export: ";
                    getline(cin, channel);
                    exportToJson(dllStore, "Exported_Payment_Channel.json", channel);
                    break;
                }
                case 0:
                    cout << "Exiting by user choice." << endl;
                    break;
                default:
                    cout << "Invalid main choice" << endl;
            }
        }while (option != 0);
    }else{
        cout << "Invalid Choice" << endl;
    }
<<<<<<< Updated upstream
=======
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
    }
    else
    {
        filteredList = list.filterByPaymentChannel(selectedChannel);
    }
    cout << "Transaction data filtered by " << selectedChannel << endl;

    // requesting user if need to print data.
    // if yes, top 300 is printed
    askAndPrintData(filtered, filteredList, structureChoice);

    // Main submenu
    int option;
    int sortingLink;
    bool check = true;
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
        {
            cout << "Sorting transaction data by location in ascending order...\n"
                 << endl;
            if (structureChoice == 1)
            {
                measureAndReport("Merge sort", [&]()
                                 { filtered.sortByLocation(); });
            }
            else
            {
                do
                {
                    cout << "1. Bubble Sort" << endl;
                    cout << "2. Insertion Sort" << endl;
                    cout << "Choose what algorithm of sorting want to use: ";
                    cin >> sortingLink;

                    if (sortingLink == 1)
                    {
                        // sort method for linkedlist (place in measureAndReport)
                        measureAndReport("Bubble sort (Linked List)", [&]()
                        {filteredList -> sortByLocation();});
                        break;
                    }else if (sortingLink == 2)
                    {
                        measureAndReport("Insertion sort (Linked List)", [&]()
                        {
                            filteredList -> insertionSortByLocation();
                        });
                        break;
                    }else
                    {
                        cout << "Wrong option. Please choose again" << endl;
                        check = false;
                    }
                }while (!check);
                
            }

            askAndPrintData(filtered, filteredList, structureChoice);
            break;
        }
        case 2:
        {
            string type;
            if (structureChoice == 1)
            {
                // search method for array (place in measureAndReport)
            }
            else
            {
                //
            }
            askAndPrintData(filtered, filteredList, structureChoice);
            break;
        }
        case 3:
        {
            cout << "Exporting transaction data...";
            string baseName = (structureChoice == 1) ? "array" : "linked_list";
            string folder = "export/";
            string ext = ".json";
            string fullPath = folder + baseName + ext;

            int counter = 1;
            while (filesystem::exists(fullPath))
            {
                fullPath = folder + baseName + "_" + to_string(counter++) + ext;
            }

            if (structureChoice == 1)
            {
                filtered.exportToJSON(fullPath);
            }
            else
            {
                filteredList->exportToJSON(fullPath);
            }
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Try again\n"
                 << endl;
        }

    } while (option != 4);
>>>>>>> Stashed changes

    return 0;
    
}