#pragma once
#include <string>
using namespace std;

class Transaction
{
public:
    string transaction_id;
    string timestamp;
    string sender_account;
    string receiver_account;
    double amount;
    string transaction_type;
    string merchant_category;
    string location;
    string device_used;
    bool is_fraud;
    string fraud_type;
    double time_since_last_transaction;
    double spending_deviation_score;
    double velocity_score;
    double geo_anomaly_score;
    string payment_channel;
    string ip_address;
    string device_hash;

    Transaction() {}

    Transaction(
        string tid, string ts, string sender, string receiver, double amt,
        string ttype, string mcat, string loc, string dev, bool fraud,
        string ftype, double tsl, double sdev, double vel, double geo,
        string pchan, string ip, string devhash)
    {
        transaction_id = tid;
        timestamp = ts;
        sender_account = sender;
        receiver_account = receiver;
        amount = amt;
        transaction_type = ttype;
        merchant_category = mcat;
        location = loc;
        device_used = dev;
        is_fraud = fraud;
        fraud_type = ftype;
        time_since_last_transaction = tsl;
        spending_deviation_score = sdev;
        velocity_score = vel;
        geo_anomaly_score = geo;
        payment_channel = pchan;
        ip_address = ip;
        device_hash = devhash;
    }
};
