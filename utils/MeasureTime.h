#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

void measureAndReport(const string &label, const function<void()> &func)
{
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << label << " completed in " << duration.count() << "ms\n";
}