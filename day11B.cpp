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
    Monkey(vector<long long > _startingItems, string _newOperation, long long  _divTest, int _falseResult, int _trueResult)
    {
        items = _startingItems;
        newOperation = _newOperation;
        divTest = _divTest;
        testOutcome[0] = _falseResult;
        testOutcome[1] = _trueResult;
    }

    vector<long long > items;
    string newOperation;
    long long  divTest;
    int testOutcome[2];
    long long  itemInspects = 0;
    long long  multiple;
    long long  getNew(long long  old)
    {
        smatch match;
        regex_search(newOperation, match, regex("= (.+) ([*|+]) (.+)"));

        long long  val1 = match[1] == "old" ? old : stol(match[1]);
        long long  val2 = match[3] == "old" ? old : stol(match[3]);

        if (match[2] == "+")
        {

            return (val1 + val2) % multiple;
        }
        else if (match[2] == "*")
        {
            return (val1 * val2) % multiple;
        }

        else
        {
            throw runtime_error("Unhandled operand");
        }
    }

    int getNewMonkeyIndex(long long  worry)
    {
        return testOutcome[worry % divTest == 0];
    }
};

vector<long long > splitCSVString(string rawString)
{
    vector<long long > returnValues;
    string stringVal = regex_replace(rawString.data(), regex("\\s+"), "");

    auto start = 0;
    auto end = stringVal.find(',');

    while (end != std::string::npos)
    {

        returnValues.push_back(stol(stringVal.substr(start, end - start)));

        start = end + 1;
        end = stringVal.find(',', start);
    }

    returnValues.push_back(stol(stringVal.substr(start, stringVal.size())));

    return returnValues;
}

long long  extractNumber(string stringVal)
{
    smatch match;
    regex_search(stringVal, match, regex("(\\d+)"));
    return stol(match[1]);
}

int main()
{

    ifstream InputFile("day11.txt");
    vector<string> inputVec;
    vector<Monkey> monkeys;
    long long  worryLevel;

    for (string line; getline(InputFile, line);)
    {
        inputVec.push_back(line);
    }

    for (int m = 0; m < inputVec.size(); m += 7)
    {

        vector<long long > startingItems = splitCSVString(inputVec[m + 1].substr(17, (inputVec[m + 1].size())));
        string operation = inputVec[m + 2];
        long long  divTest = extractNumber(inputVec[m + 3]);
        int trueResult = extractNumber(inputVec[m + 4]);
        int falseResult = extractNumber(inputVec[m + 5]);

        monkeys.push_back(Monkey(startingItems, operation, divTest, falseResult, trueResult));
    }

    long long  multipleVal = 1;

    for (auto monkey : monkeys)
    {
        multipleVal *= monkey.divTest;
    }

    for (auto &monkey : monkeys)
    {
        monkey.multiple = multipleVal;
    }

    print("Multi Value: "+to_string(multipleVal));

    for (int round = 0; round < 10000; round++)
    {

        cout << "Round: " << round << '\r' << flush;

        for (auto &monkey : monkeys)
        {

            for (auto &item : monkey.items)
            {

                worryLevel = monkey.getNew(item);

                monkeys[monkey.getNewMonkeyIndex(worryLevel)].items.push_back(worryLevel);
                monkey.itemInspects++;
            }

            monkey.items.clear();
        }
    }

    vector<long long > inspects;

    transform(monkeys.cbegin(), monkeys.cend(), back_inserter(inspects), [](Monkey monkey)
              { return monkey.itemInspects; });

    sort(inspects.rbegin(), inspects.rend());

    print(inspects[0] * inspects[1]);
}
