#include <fstream>
#include <iostream>
#include <regex>
#include <cctype>
#include <array>

#define numberOfStacks 9
#define print(x) std::cout << x << std::endl

using namespace std;

array<string, numberOfStacks> stacks;

int main()
{
    ifstream InputFile("week5.txt");

    bool readingStacks = true;

    for (string line; getline(InputFile, line);)
    {

        if (readingStacks)
        {

            readingStacks = !any_of(line.begin(), line.end(), ::isdigit);

            for (int i = 1; i < line.size(); i += 4)
            {
                if (isalpha(line[i]))
                {
                    stacks[i / 4] = line[i] + stacks[i / 4];
                }
            }
        }
        else
        {

            smatch match;

            regex_search(line, match, regex("move (\\d+) from (\\d+) to (\\d+)"));
            if (match.size() == 4)
            {
                string stringToTake = stacks[stoi(match[2]) - 1];
                string stringKeep = stringToTake.substr(0, stringToTake.size() - stoi(match[1]));
                string stringMove = stringToTake.substr(stringToTake.size() - stoi(match[1]), stringToTake.size());

                stacks[stoi(match[2]) - 1] = stringKeep;
                stacks[stoi(match[3]) - 1] += stringMove;
            }
        }
    }

    string result = "";
    for (auto stack : stacks)
    {
        result += stack[stack.size() - 1];
    }
    print(result);
}