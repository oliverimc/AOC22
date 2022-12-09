#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#define print(x) std::cout << x << std::endl

using namespace std;

int main()
{
    ifstream InputFile("week3.txt");
    int itemPriority = 0, badgePriority = 0, count = 0;
    set<char> group[3];

    for (string backpack; getline(InputFile, backpack); count++)
    {

        set<char> firstHalf(backpack.begin(), backpack.begin() + backpack.size() / 2);
        set<char> secondHalf(backpack.begin() + backpack.size() / 2, backpack.end());
        vector<char> intersection;
        set_intersection(firstHalf.begin(), firstHalf.end(), secondHalf.begin(), secondHalf.end(), back_inserter(intersection));
        itemPriority += (int)intersection[0] - (isupper(intersection[0]) ? 38 : 96);

        group[count % 3] = set<char>(backpack.begin(), backpack.end());

        if (count % 3 == 2)
        {
            vector<char> intersection12;
            vector<char> intersection123;

            set_intersection(group[0].begin(), group[0].end(), group[1].begin(), group[1].end(), back_inserter(intersection12));
            set_intersection(intersection12.begin(), intersection12.end(), group[2].begin(), group[2].end(), back_inserter(intersection123));

            badgePriority += (int)intersection123[0] - (isupper(intersection123[0]) ? 38 : 96);
        }
    }
    print(itemPriority);
    print(badgePriority);
}