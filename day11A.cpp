#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#define print(x) std::cout << x << std::endl

using namespace std;

class Monkey
{
public:
    Monkey(vector<int> _startingItems, string _newOperation, int _divTest, int _falseResult, int _trueResult)
    {
        items = _startingItems;
        newOperation = _newOperation;
        divTest = _divTest;
        testOutcome[0] = _falseResult;
        testOutcome[1] = _trueResult;
    }

    vector<int> items;
    string newOperation;
    int divTest;
    int testOutcome[2];
    int itemInspects = 0;
    int getNew(int old)
    {
        smatch match;
        regex_search(newOperation, match, regex("= (.+) ([*|+]) (.+)"));

        int val1 = match[1] == "old" ? old : stoi(match[1]);
        int val2 = match[3] == "old" ? old : stoi(match[3]);

        if (match[2] == "+")
        {

            return val1 + val2;
        }
        else if (match[2] == "*")
        {
            return val1 * val2;
        }

        else
        {
            throw runtime_error("Unhandled operand");
        }
    }

    int getNewMonkeyIndex(int worry)
    {
        return testOutcome[worry % divTest == 0];
    }
};

vector<int> splitCSVString(string rawString)
{
    vector<int> returnValues;
    string stringVal = regex_replace(rawString.data(), regex("\\s+"), "");

    auto start = 0;
    auto end = stringVal.find(',');

    while (end != std::string::npos)
    {

        returnValues.push_back(stoi(stringVal.substr(start, end - start)));

        start = end + 1;
        end = stringVal.find(',', start);
        ;
    }

    returnValues.push_back(stoi(stringVal.substr(start, stringVal.size())));

    return returnValues;
}

int extractNumber(string stringVal)
{
    smatch match;
    regex_search(stringVal, match, regex("(\\d+)"));
    return stoi(match[1]);
}

int main()
{

    ifstream InputFile("day11.txt");
    vector<string> inputVec;
    vector<Monkey> monkeys;
    int worryLevel;

    for (string line; getline(InputFile, line);)
    {
        inputVec.push_back(line);
    }

    for (int m = 0; m < inputVec.size(); m += 7)
    {

        vector<int> startingItems = splitCSVString(inputVec[m + 1].substr(17, (inputVec[m + 1].size())));
        string operation = inputVec[m + 2];
        int divTest = extractNumber(inputVec[m + 3]);
        int trueResult = extractNumber(inputVec[m + 4]);
        int falseResult = extractNumber(inputVec[m + 5]);

        monkeys.push_back(Monkey(startingItems, operation, divTest, falseResult, trueResult));
    }

    for (int round = 0; round < 20; round++)
    {
        int monkeyCounter = 0;

        for (auto &monkey : monkeys)
        {

            for (auto &item : monkey.items)
            {

                worryLevel = monkey.getNew(item);
                worryLevel /= 3;

                monkeys[monkey.getNewMonkeyIndex(worryLevel)].items.push_back(worryLevel);
                monkey.itemInspects++;
            }

            monkey.items.clear();
            monkeyCounter++;
        }
    }

    vector<int> inspects;

    transform(monkeys.cbegin(), monkeys.cend(), back_inserter(inspects), [](Monkey monkey)
              { return monkey.itemInspects; });

    sort(inspects.rbegin(), inspects.rend());

    print(inspects[0] * inspects[1]);
}
