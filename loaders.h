#ifndef LOADERS_H
#define LOADERS_H
using namespace std;

#include <string>
#include "TransactionDLL.h"

void loadDataIntoDLL(TransactionDLL& dll, const string& filename, int limit = 300);

#endif