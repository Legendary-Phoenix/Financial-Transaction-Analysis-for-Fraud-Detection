#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string name;
    string exit;
    bool loop = true;
    while (loop)
    {
        cout << "What's your name? ";
        getline(cin, name); // Read full line including spaces

        cout << "Hello, " << name << "! Welcome to C++ in VS Code." << endl;
        cout << "End Program? (Y/N)";
        getline(cin, exit);

        if (exit == "Y" || exit == "y")
        {
            return 0;
        };
    }
}
