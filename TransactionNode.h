#pragma once
#include "Transaction.h"

struct TransactionNode
{
    Transaction data;
    TransactionNode *next;

    TransactionNode(Transaction t)
    {
        data = t;
        next = nullptr;
    }
};