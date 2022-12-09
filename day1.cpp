#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>

#define print(x) std::cout << x << std::endl

using namespace std;

int main()
{
    ifstream InputFile("week1.txt");

    int groupSum = 0;
    vector<int> elfAmounts;

    for (string line; getline(InputFile, line);)
    {
        if (line == "")
        {
            elfAmounts.push_back(groupSum);
            groupSum = 0;
        }

        else
        {
            line.erase(remove(line.begin(), line.end(), '\n'), line.cend());
            groupSum += stoi(line);
        }
    }
    elfAmounts.push_back(groupSum);

    sort(elfAmounts.begin(), elfAmounts.end(), greater<int>());
    print(elfAmounts[0]);
    print(reduce(elfAmounts.begin(), elfAmounts.begin() + 3));
}