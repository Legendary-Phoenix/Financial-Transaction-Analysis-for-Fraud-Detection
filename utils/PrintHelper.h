#pragma once

#include "../TransactionArray.h"
#include "../TransactionLinkedList.h"
#include <iostream>

void askAndPrintData(const TransactionArray &array, const TransactionLinkedList *list, int structureChoice)
{
    std::cout << "\nDo you want to print the top 300 of the transaction data?\n";
    std::cout << "Enter 'Y' for yes, anything else for no: ";

    std::string printChoice;
    std::cin >> printChoice;

    if (printChoice == "y" || printChoice == "Y")
    {
        if (structureChoice == 1)
        {

            array.printAll();
        }
        else
        {

            list->printAll();
        }
    }
}
