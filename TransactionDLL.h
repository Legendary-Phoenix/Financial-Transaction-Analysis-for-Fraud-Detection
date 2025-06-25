#ifndef TRANSACTION_DLL_H
#define TRANSACTION_DLL_H
#include "Transaction.h"

using namespace std;

#include <string>
// DEFINING TRANSACTION STRUCT SEPARATELY
#include "Transaction.h"

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
        void searchByTrancsactionType(const string& type);
        void displayByPaymentChannel(const string& channel);
        void clear();
};

#endif
