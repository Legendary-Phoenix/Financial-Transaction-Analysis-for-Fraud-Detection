#include <iostream>
#include "TransactionDLL.h"
using namespace std;

TransactionDLL::TransactionDLL() : head(nullptr), tail(nullptr) {}

TransactionDLL::~TransactionDLL(){
    clear();
}

void TransactionDLL::add(Transaction t){
    Node* newNode = new Node{t, tail, nullptr};

    if(!head) {
        head = tail = newNode;
    } else {
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }
}

void TransactionDLL::printAll(){

}