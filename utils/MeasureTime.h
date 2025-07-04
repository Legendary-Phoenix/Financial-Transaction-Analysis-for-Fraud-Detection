#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

// for functions that don't return anything which will be the sorting functions
void measureAndReport(const string &label, const function<void()> &func)
{
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();

    auto durationMs = duration_cast<milliseconds>(end - start);
    double durationMinutes = durationMs.count() / 60000.0; // 1 min = 60000 ms

    cout << label << " completed in " << durationMs.count() << " ms ";
    cout << "(" << fixed << setprecision(4) << durationMinutes << " minutes)" << endl;
}

// for functions that return a result which in this case are search functions
template <typename Func>
auto measureAndReturn(const string &label, Func func) -> decltype(func())
{
    auto start = high_resolution_clock::now();
    auto result = func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << label << " completed in " << duration.count() << " ms\n";
    return result;
}