#ifndef TRANSACTION_DLL_H
#define TRANSACTION_DLL_H
#include "Transaction.h"
using namespace std;

#include <string>
// DEFINING TRANSACTION STRUCT SEPARATELY
#include <unordered_set>

struct Node {
    Transaction data;
    Node* prev;
    Node* next;
};

class TransactionDLL {
    private:
        Node* head;
        Node* tail;

    public:
        TransactionDLL();
        ~TransactionDLL();

        void add(Transaction t);
        void printAll();
        void sortByLocation(); //IMPLEMENTING MERGE SORT OR BUBBLE SORT
        void searchByTransactionType(const string& type);
        void displayByPaymentChannel(const string& channel);
        void displayAllByPaymentChannel();
        void exportToJson(const string& filename, const string& filterChannel);
        void clear();

        Node* getHead() const;
};

#endif
