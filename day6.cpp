#include <fstream>
#include <iostream>
#include <unordered_set>

#define print(x) std::cout << x << std::endl

using namespace std;

int main()
{
    ifstream InputFile("week6.txt");
    string signal;
    getline(InputFile, signal);

    for (int i = 0; i < signal.size() - 4; i++)
    {
 

        if (unordered_set<char>(signal.begin() + i, signal.begin() + i + 4).size() == 4)
        {
            print(i + 4);
            break;
        }
    }
    for (int i = 0; i < signal.size() - 14; i++)
    {
        if (unordered_set<char>(signal.begin() + i, signal.begin() + i + 14).size() == 14)
        {
            print(i + 14);
            break;
        }
    }
}
