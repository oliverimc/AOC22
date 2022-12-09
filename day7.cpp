#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <numeric>

#define print(x) std::cout << x << std::endl

using namespace std;

class Directory
{
public:
    Directory(Directory *parent) { this->parentDirectory = parent; };
    vector<int> files;
    map<string, Directory *> subDirectories;
    Directory *parentDirectory;
};

int sumVec(vector<int> vec)
{
    return accumulate(vec.begin(), vec.end(), 0);
}

int evalDir(Directory dir, int &smallDirTotal, int &currentRemoveDir)
{
    int fileTotal = sumVec(dir.files);

    if (dir.subDirectories.size() > 0)
    {

        for (auto dir : dir.subDirectories)
        {
            fileTotal += evalDir(*dir.second, smallDirTotal, currentRemoveDir);
        }
    }

    if (fileTotal <= 100000)
    {
        smallDirTotal += fileTotal;
    }

    if (fileTotal >= 8381165 && fileTotal <= currentRemoveDir)
    {
        currentRemoveDir = fileTotal;
    }

    return fileTotal;
}

int main()
{

    ifstream InputFile("day7.txt");

    Directory *root = new Directory(NULL);
    Directory *current = root;

    string line;
    getline(InputFile, line);

    while (!InputFile.eof())
    {

        if (line.substr(2, 2) == "cd")
        {
            if (line.substr(5, line.size()) == "..")
            {
                current = current->parentDirectory;
            }
            else
            {
                string name = line.substr(5, line.size());
                current->subDirectories.insert(pair<string, Directory *>(name, new Directory(current)));
                current = current->subDirectories[name];
            }

            getline(InputFile, line);
        }
        else if (line.substr(2, 2) == "ls")
        {
            do
            {
                getline(InputFile, line);
                if (line[0] != 'd' && line[0] != '$')
                {
                    smatch match;
                    regex_search(line, match, regex("(\\d+)"));
                    current->files.push_back(stoi(match[1]));
                }

            } while (line[0] != '$' && !InputFile.eof());
        }
    }

    int smallTotal = 0, currentRemoveVal = INT_MAX;
    evalDir(*root->subDirectories["/"], smallTotal, currentRemoveVal);
    print(smallTotal);
    print(currentRemoveVal);
}
