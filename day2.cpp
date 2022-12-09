#include <iostream>
#include <fstream>
#include <map>
#include <string>

#define print(x) std::cout << x << std::endl

using namespace std;

// PART 1
map<char, int> shapeScore{{'X', 1}, {'Y', 2}, {'Z', 3}};

map<char, int> XScore{{'A', 3}, {'B', 0}, {'C', 6}};
map<char, int> YScore{{'A', 6}, {'B', 3}, {'C', 0}};
map<char, int> ZScore{{'A', 0}, {'B', 6}, {'C', 3}};

map<char, map<char, int>> playScore{{'X', XScore}, {'Y', YScore}, {'Z', ZScore}};

// PART 2
map<char, int> resultScore{{'X', 0}, {'Y', 3}, {'Z', 6}};

map<char, int> LoseScore{{'A', 3}, {'B', 1}, {'C', 2}};
map<char, int> DrawScore{{'A', 1}, {'B', 2}, {'C', 3}};
map<char, int> WinScore{{'A', 2}, {'B', 3}, {'C', 1}};

map<char, map<char, int>> decisionScore{{'X', LoseScore}, {'Y', DrawScore}, {'Z', WinScore}};

int main()
{

    int part1Score = 0, part2Score = 0;
    ifstream InputFile("day2.txt");

    for (string round; getline(InputFile, round);)
    {
        char opponent = round[0];
        char play = round[2];

        part1Score += shapeScore[play] + playScore[play][opponent];
        part2Score += resultScore[play] + decisionScore[play][opponent];
    }
    print(part1Score);
    print(part2Score);
}