#include <fstream>
#include <iostream>
#include <regex>
#include <queue>
#include <cctype>

#include <array>

#define numberOfStacks 9
#define print(x) std::cout << x << std::endl

using namespace std;

array<deque<char>, numberOfStacks> stacks;

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
                    stacks[i / 4].push_front(line[i]);
                }
            }
        }

        else
        {

            smatch match;

            regex_search(line, match, regex("move (\\d+) from (\\d+) to (\\d+)"));
            if (match.size() == 4)
            {

                for (int i = 0; i < stoi(match[1]); i++)
                {

                    stacks[stoi(match[3]) - 1].push_back(stacks[stoi(match[2]) - 1].back());
                    stacks[stoi(match[2]) - 1].pop_back();
                }
            }
        }
    }

    string result = "";
    for (auto stack : stacks)
    {
        result += stack.back();
    }
    print(result);
}