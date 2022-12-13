#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define print(x) std::cout << x << std::endl

using namespace std;

class Node
{
public:
    Node()
    {
    }
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

    bool isList = true;
    int value;
    vector<Node> values;

    bool operator==(const Node &rhs) const
    {
        if (isList == rhs.isList)
        {
            if (isList)
            {
                return values == rhs.values;
            }
            else
            {
                return value == rhs.value;
            }
        }
        else
        {
            return false;
        }
    }

    bool operator<(const Node &other) const
    {

        if (!isList && !other.isList)
        {

            return value < other.value;
        }

        else if (isList && other.isList)
        {
            for (int n = 0; n < values.size(); n++)
            {
                if (n == other.values.size())
                {

                    return false;
                }
                else if (values[n] < other.values[n])
                {

                    return true;
                }
                else if (other.values[n] < values[n])
                {
                    return false;
                }
            }

            return values.size() != other.values.size();
        }

        else
        {
            Node thisList, otherList;

            if (this->isList)
            {
                thisList = *this;
            }
            else
            {
                thisList.isList = true;
                thisList.values = {Node(value)};
            }

            if (other.isList)
            {
                otherList = other;
            }
            else
            {
                otherList.isList = true;
                otherList.values = {Node(other.value)};
            }

            return thisList < otherList;
        }
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
        }

        return -1; // Indicates there is no "]"" present
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
                int endInteger = indexOfClosingBracket(dataString.substr(i + 1, dataString.size())) + i + 1;
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

        indSum += first < second ? (i / 3 + 1) : 0;
    }

    print(indSum);

    Node twoKey = Node("[[2]]");
    Node sixKey = Node("[[6]]");

    nodes.push_back(twoKey);
    nodes.push_back(sixKey);

    sort(nodes.begin(), nodes.end());

    int ind2 = distance(nodes.begin(), find(nodes.begin(), nodes.end(), twoKey)) + 1;
    int ind6 = distance(nodes.begin(), find(nodes.begin(), nodes.end(), sixKey)) + 1;

    print(ind2 * ind6);
}