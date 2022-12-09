#include <fstream>
#include <iostream>
#include <regex>

#define print(x) std::cout << x << std::endl

using namespace std;

int main()
{
    ifstream InputFile("week4.txt");
    int encloses = 0, overlaps = 0;
    for (string pair; getline(InputFile, pair);)
    {

        smatch match;
        regex_search(pair, match, regex("(\\d+)-(\\d+),(\\d+)-(\\d+)"));

        int low1 = stoi(match[1]);
        int high1 = stoi(match[2]);

        int low2 = stoi(match[3]);
        int high2 = stoi(match[4]);

        if ((low1 <= low2 && high1 >= high2) || (low2 <= low1) && (high2 >= high1))
        {
            encloses++;
        }

        if (!((high1<low2)||(high2<low1)))
        {
            overlaps++;
        }
    }

    print(encloses);
    print(overlaps);
}
