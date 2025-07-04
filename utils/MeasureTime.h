/*#pragma once

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
}*/

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

    auto durationMs = duration_cast<milliseconds>(end - start);
    double durationMinutes = durationMs.count() / 60000.0; // 1 min = 60000 ms

    cout << label << " completed in " << durationMs.count() << " ms ";
    cout << "(" << fixed << setprecision(4) << durationMinutes << " minutes)" << endl;
}
