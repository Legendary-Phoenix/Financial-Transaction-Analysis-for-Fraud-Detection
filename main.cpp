#include "TransactionArray.cpp"
#include <fstream>
#include <sstream>

int main()
{

    TransactionArray arrStore;

    // Load from CSV
    ifstream file("data/financial_fraud_detection_dataset.csv");
    if (!file.is_open())
    {
        cerr << "Failed to open file!" << endl;
        perror("Error");
        return 1;
    }
    cout << "I reach here:" << endl;
    string line;
    getline(file, line);
    int count = 0;

    while (getline(file, line) && count < 1000000)
    {
        stringstream ss(line);
        string values[18], token;
        int i = 0;
        while (getline(ss, token, ',') && i < 18)
        {
            values[i++] = token;
        }

        if (i == 18)
        {
            try
            {
                double amount = values[4].empty() ? 0.0 : stod(values[4]);
                double tsl = values[11].empty() ? 0.0 : stod(values[11]);
                double sdev = values[12].empty() ? 0.0 : stod(values[12]);
                double vel = values[13].empty() ? 0.0 : stod(values[13]);
                double geo = values[14].empty() ? 0.0 : stod(values[14]);

                Transaction t(
                    values[0], values[1], values[2], values[3], amount,
                    values[5], values[6], values[7], values[8], values[9] == "TRUE",
                    values[10], tsl, sdev, vel,
                    geo, values[15], values[16], values[17]);
                arrStore.add(t);
                count++;
            }
            catch (const std::exception &e)
            {
                cerr << "⚠️ Error on line " << count + 1 << ": " << e.what() << endl;
                cerr << "Line: " << line << endl;
            }
        }
    }
    file.close();
    cout << "Loaded " << count << " transactions into array" << endl;
}