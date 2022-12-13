#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define print(x) std::cout << x << std::endl

using namespace std;

class Node
{
public:
    Node(int _value)
    {
        value = _value;
        isList = false;
    }

    Node(string _values)
    {
        isList = true;
        values = parseNodes(_values);
    }

    bool isList = true; // Default such that an empty list is left as a list type
    int value;
    vector<Node> values;
    Node makeList()
    {
        return Node("[" + to_string(value) + "]");
    }

    string toString() const
    {
        if (isList)
        {
            string nodeString = "[";
            for (auto val : values)
            {
                nodeString += val.toString() + ",";
            }
            // If there are no values don't remove the last value (since there is no extra comma)
            return (nodeString.size() > 1 ? nodeString.substr(0, nodeString.size() - 1) : nodeString) + "]";
        }
        else
        {
            return to_string(value);
        }
    }
    friend ostream &operator<<(ostream &os, const Node &node)
    {
        os << node.toString();
        return os;
    }

private:
    int indexOfClosingBracket(string stringVal)
    {
        int openersEncountered = 0;

        for (int i = 0; i < stringVal.size(); i++)
        {
            char character = stringVal[i];

            if (character == '[')
            {
                openersEncountered++;
            }
            else if (character == ']')
            {
                if (openersEncountered == 0)
                {

                    return i;
                }
                else
                {
                    openersEncountered--;
                }
            }
            else
            {
                // Do nothing
            }
        }

        return -1; // Should never return, indicates error
    }
    vector<Node> parseNodes(string values)
    {

        vector<Node> parsedList;
        string dataString = values.substr(1, values.size());
        int i = 0;

        while (i < dataString.size())
        {

            if (dataString[i] == '[')
            {
                int endInteger = indexOfClosingBracket(dataString.substr(i + 1, dataString.size())) + i + 1; // +1 to account for shift
                parsedList.push_back(Node(dataString.substr(i, endInteger - i + 1)));
                i = endInteger + 1;
            }
            else if (dataString[i] == ',' || dataString[i] == ']')
            {
                i++;
            }
            else
            {
                int numberStart = i;
                while (dataString[i] != ',' && dataString[i] != ']')
                {
                    i++;
                }
                parsedList.push_back(Node(stoi(dataString.substr(numberStart, i - numberStart))));
            }
        }
        return parsedList;
    }
};

int isCorrect(Node smaller, Node larger)
{
    // 1 = Yes, 0 = No, -1 = Unknown keep checking

    if (!smaller.isList && !larger.isList)
    {
        if (smaller.value < larger.value)
        {
            return 1;
        }

        else if (smaller.value > larger.value)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    else if (smaller.isList && larger.isList)
    {
        for (int n = 0; n < smaller.values.size(); n++)
        {
            if (n == larger.values.size())
            {
                return false;
            }
            int correctValue = isCorrect(smaller.values[n], larger.values[n]);

            switch (correctValue)
            {
            case 1:
                return 1;
                break;
            case 0:
                return 0;
                break;
            case -1:
                // pass
                break;
            default:
                throw runtime_error("Unreachable code, issue found.");
                break;
            }
        }
        return smaller.values.size() == larger.values.size() ? -1 : 1;
    }

    else
    {
        Node listSmaller = smaller.isList ? smaller : smaller.makeList();
        Node listLarger = larger.isList ? larger : larger.makeList();
        return isCorrect(listSmaller, listLarger);
    }
}

int main()
{

    ifstream InputFile("day13.txt");
    vector<string> inputVec;

    for (string line; getline(InputFile, line);)
    {
        inputVec.push_back(line);
    }

    vector<Node> nodes;
    int indSum = 0;

    for (int i = 0; i < inputVec.size(); i += 3)
    {

        Node first(inputVec[i]);
        Node second(inputVec[i + 1]);

        nodes.push_back(first);
        nodes.push_back(second);

        // Top level nodes should always be lists, otherwise indicates parsing error
        assert(first.isList);
        assert(second.isList);

        indSum += isCorrect(first, second) ? (i / 3 + 1) : 0;
    }

    Node twoKey = Node("[[2]]");
    Node sixKey = Node("[[6]]");

    nodes.push_back(twoKey);
    nodes.push_back(sixKey);

    print(indSum);
    sort(nodes.begin(), nodes.end(), [](const Node &node1, const Node &node2)
         { return isCorrect(node1, node2) == 1 ? true : false; });

    int ind6, ind2;
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].values.size() == 1)
        {
            if (nodes[i].values[0].values.size() == 1)
            {
                if (nodes[i].values[0].values[0].value == 2)
                {
                    ind2 = i + 1;
                }
                else if (nodes[i].values[0].values[0].value == 6)
                {
                    ind6 = i + 1;
                }
                 
            }
        }
    }

    print(ind2 * ind6);
}