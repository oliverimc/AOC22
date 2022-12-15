#include <algorithm>
#include <fstream>
#include <iostream>

#include <utility>
#include <vector>
#include <regex>

#define print(x) std::cout << x << std::endl

using namespace std;

void printCave(vector<vector<short>> caveMap)
{
    for (auto row : caveMap)
    {
        for (auto cell : row)
        {
            if (cell ==1)
            {
                cout <<"#";
            }
            else if (cell ==0)
            {
                cout<<".";
            }
            else 
            {
                cout << "o";
            }
        }

        cout << endl;
    }
}

int main()
{

    ifstream InputFile("day14.txt");
    vector<vector<pair<int, int>>> paths;

    int maxX = 500, maxY = 0, minX = 500, minY = 0;

    for (string line; getline(InputFile, line);)
    {
        vector<pair<int, int>> path;

        regex coordRegex("(\\d+),(\\d+)");
        auto regexIt = sregex_iterator(line.begin(), line.end(), coordRegex)++;
        for (; regexIt != sregex_iterator(); regexIt++)
        {
            pair<int, int> coord(stoi((*regexIt)[1]), stoi((*regexIt)[2]));

            maxX = max(maxX, coord.first);
            maxY = max(maxY, coord.second);
            minX = min(minX, coord.first);
            minY = min(minY, coord.second);

            path.push_back(coord);
        }

        paths.push_back(path);
    }
    vector<vector<short>> caveMap(maxY - minY + 1,vector<short>(maxX - minX + 1));
    for (auto path : paths)
    {
        for (int i = 0; i < path.size() - 1; i++)
        {
            auto [rawCS, rawRS] = path[i];     // Start
            auto [rawCE, rawRE] = path[i + 1]; // End

            int rStart = rawRS - minY;
            int rEnd = rawRE - minY;

            int cStart = rawCS - minX;
            int cEnd = rawCE - minX;

            for (int r = rStart; r != rEnd + (rStart < rEnd ? 1 : -1); r += (rStart < rEnd ? 1 : -1))
            {
                for (int c = cStart; c != cEnd + (cStart < cEnd ? 1 : -1); c += (cStart < cEnd ? 1 : -1))
                {
                    caveMap[r][c] = true;
                }
            }
        }
    }

    bool caveFull = false;
    int sandGrains = 0;

    while (!caveFull)
    {
        int grainCol = 500 - minX, grainRow = 0;
        
        
        bool sandBlocked = false;
       
        while (!sandBlocked )
        {
            if (grainRow + 1 >= caveMap.size())
            {
                
                caveFull = true;
                sandBlocked = true;
            }

            else if (caveMap[grainRow + 1][grainCol]==0)
            {
                grainRow++;
            }
            else if (caveMap[grainRow + 1][grainCol - 1]==0)
            {
                grainRow++;
                grainCol--;
            }
            else if (caveMap[grainRow + 1][grainCol + 1]==0)
            {
                grainRow++;
                grainCol++;
            }
            else
            {

                
                sandBlocked = true;
                caveMap[grainRow][grainCol] = -1;
                sandGrains++;
            }
        }
    }

   
    print(sandGrains);
}
