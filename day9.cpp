#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

#define print(x) std::cout << x << std::endl

using namespace std;

void incrementPos(pair<int, int> &head, char direction)
{
    switch (direction)
    {
    case 'U':
        head.second++;
        break;
    case 'D':
        head.second--;
        break;
    case 'R':
        head.first++;
        break;
    case 'L':
        head.first--;
        break;

    default:
        break;
    }
}

int simulateNRope(string inputFile, int n)
{

    ifstream InputFile(inputFile);

    vector<pair<int, int>> rope(n);
    set<pair<int, int>> visited;

    visited.insert(rope.back()); // Add the starting position

    for (string cmd; getline(InputFile, cmd);)
    {
        char direction = cmd[0];
        int moves = stoi(cmd.substr(2, cmd.size()));

        for (int i = 0; i < moves; i++)
        {
            incrementPos(rope.front(), direction);
            for (int j = 1; j < rope.size(); j++)
            {

                if (rope[j - 1].first == rope[j].first && rope[j - 1].second == rope[j].second)
                {
                    // Do nothing
                }

                // Vertical
                else if (rope[j - 1].first == rope[j].first && abs(rope[j - 1].second - rope[j].second) > 1)
                {

                    rope[j].second += rope[j].second < rope[j - 1].second ? 1 : -1;
                }

                // Horizontal
                else if (rope[j - 1].second == rope[j].second && abs(rope[j - 1].first - rope[j].first) > 1)
                {

                    rope[j].first += rope[j].first < rope[j - 1].first ? 1 : -1;
                }

                // Diagonal
                else if ((abs(rope[j - 1].second - rope[j].second) + abs(rope[j - 1].first - rope[j].first)) > 2)
                {

                    rope[j].first += rope[j].first < rope[j - 1].first ? 1 : -1;
                    rope[j].second += rope[j].second < rope[j - 1].second ? 1 : -1;
                }
            }

            visited.insert(rope.back());
        }
    }

    return visited.size();
}

int main()
{
    print(simulateNRope("day9.txt", 2));
    print(simulateNRope("day9.txt", 10));
}