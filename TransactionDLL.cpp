#include <iostream>
#include "TransactionDLL.h"
#include "loaders.h"
#include <fstream>
#include <sstream>
#include <nlohman/json.hpp>
using namespace std;

TransactionDLL::TransactionDLL() : head(nullptr), tail(nullptr) {}

TransactionDLL::~TransactionDLL(){
    clear();
}

void TransactionDLL::add(Transaction t){
    Node* newNode = new Node{t, tail, nullptr};

    if(!head){
        head = tail = newNode;
    }else{
        tail->next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }
}

void TransactionDLL::printAll(){
    Node* current = head;

    int index = 0;

    while (current){
        cout << "Transaction #" << ++index << endl;
        cout << " ID: " << current -> data.transaction_id << "\n"
             << " Location: " << current -> data.location << "\n"
             << " Type: " << current -> data.transaction_type << "\n"
             << " Channel: " << current -> data.payment_channel << "\n"
             << " Amount: $" << current -> data.amount << "\n"
             << "------------------------------------\n";
        current = current -> next;
    }
}

void TransactionDLL::displayByPaymentChannel(const string& channel){
    Node* current = head;
    bool found = false;

    while (current){
        if(current -> data.payment_channel == channel){
            cout << "ID: " << current -> data.transaction_id
                 << " | Channel: " << current -> data.payment_channel
                 << " | Type: " << current -> data.transaction_type
                 << " | Amount: $" ,, current -> data.amount << endl;
            found = true;
        }
        current = current -> next;
    }

    if (!found) {
        cout << "No transaction found for the payment channel: " << channel << endl;
    }
}

void TransactionDLL::displayAllByPaymentChannel(){
    unordered_set<string> showChannels;
    Node* current = head;

    while (current){
        string channel = current -> data.payment_channel;

        if (shownChannels.find(channel) == showChannels.end()){
            shownChannels.insert(channel);
            cout << "\n Payment Channel: " << channel << endl;
            cout << "---------------------------------------" << endl;

            Node* temp = head;
            while (temp) {
                if(temp -> data.payment_channel == channel){
                    cout << "ID: " << temp -> data.transaction_id
                         << " | Type: " << temp -> data.transaction_type
                         << " | Location: " << temp -> data.location
                         << " | Amount: $" << temp -> data.amount << endl;
                }
                temp = temp -> next;
            }
        }
        current = current -> next;
    }
}

void TransactionDLL::searchByTrancsactionType(const string& type){
    Node* current = head;
    bool found = false;

    while (current){
        if (current -> data.transaction_type == type){
            cout << "ID: " << current -> data.transaction_id
                 << " | Type: " << current -> data.transaction_type
                 << " | Location: " << current -> data.location
                 << " | Amount $" << current -> data.transaction_id << endl;

                found = true;
        }
        current = current -> next;
    }

    if (!found) {
        count << "No transaction found for the type" << type << endl;
    }
}

void TransactionDLL:sortByLocation(){
    if (!head) return;

    bool swapped;
    Node* current;

    do{
        swapped = false;
        current = head;

        while (current -> next) {
            if (current -> data.location > current -> next -> data.location){
                swap(current -> data, current -> next -> data);
                swapped = true;
            }
            current = current -> next;
        }
    }while (swapped);
}

void TransactionDLL::exportToJson(const string& filename, const string& filterChannel){
    json j;
    Node* current = head;

    while (current) {
        if(current -> data.payment_channel == filterChannel){
            j.push_back({
                {"transaction_id", current -> data.transaction_id},
                {"timestamp", current -> data.timestamp},
                {"sender_account", current -> data.sender_account},
                {"receiver_account", current -> data.receiver_account},
                {"amount", current -> data.amount},
                {"transaction_type", current -> data.transaction_type},
                {"merchant_catregory", current -> data.merchant_category},
                {"location", current -> data.location},
                {"device_used", current -> data.device_used},
                {"is_fraud", current -> data.is_fraud},
                {"fraud_type", current -> data.fraud_type},
                {"time_since_last_transaction", current -> data.time_since_last_transaction},
                {"spending_deviation_score", current -> data.spending_deviation_score},
                {"velocity_score", current -> data.velocity_score},
                {"geo_anomaly_score", current -> data.geo_anomaly_score},
                {"payment_channel", current -> data.payment_channel},
                {"ip_address", current -> data.ip_address},
                {"device_hash", current -> data.device_hash}
            });
        }
        current = current -> next;
    }
    ofstream file(filename);
    if(file.is_open()) {
        file << j.dump(4);
        cout << "Successfully exported transaction to: " << filename << endl;
    }else{
        cerr << "Failed to write JSON to file" << endl;
    }
}

void TransactionDLL::clear(){
    Node* current = head;
    while (current) {
        Node* nextNode = current -> next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
}