#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define print(x) std::cout << x << std::endl

using namespace std;

bool validPoint(pair<int, int> previous, pair<int, int> point, vector<vector<int>> const &heightMap)
{
    return point.first >= 0 &&
           point.second >= 0 &&
           point.first < heightMap.size() &&
           point.second < heightMap[0].size() &&
           (heightMap[point.first][point.second] - heightMap[previous.first][previous.second]) < 2;
}

int shortestPath(vector<pair<int, int>> starts, pair<int, int> end, vector<vector<int>> const &heightMap)
{
    set<pair<int, int>> visited;
    queue<pair<int, int>> toVisit;
    map<pair<int, int>, int> distance;

    for (auto start : starts)
    {
        visited.insert(start);
        toVisit.push(start);
        distance.insert(make_pair(start, 0));
    }

    while (!toVisit.empty())
    {
        pair<int, int> point = toVisit.front();
        toVisit.pop();

        auto options = {make_pair(point.first + 1, point.second),
                        make_pair(point.first - 1, point.second),
                        make_pair(point.first, point.second + 1),
                        make_pair(point.first, point.second - 1)};

        for (auto option : options)
        {
            if (validPoint(point, option, heightMap) && visited.count(option) == 0)
            {

                visited.insert(option);
                int distanceToPoint = distance[point] + 1;
                distance.insert(make_pair(option, distanceToPoint));
                toVisit.push(option);
            }
        }
    }

    return distance[end];
}

int main()
{
    ifstream InputFile("day12.txt");

    vector<vector<int>> heightMap;

    vector<pair<int, int>> starts;
    pair<int, int> sStart,end;

    for (string line; getline(InputFile, line);)
    {
        vector<int> row;

        for (auto cell : line)
        {
            if (cell == 'S' || cell == 'a')
            {
                if(cell=='S')
                {
                    sStart = make_pair(heightMap.size(), row.size());
                }
                
                starts.push_back(make_pair(heightMap.size(), row.size()));
                row.push_back('a');
            }
            else if (cell == 'E')
            {
                end = make_pair(heightMap.size(), row.size());
                row.push_back('z');
            }

            else
            {
                row.push_back(cell);
            }
        }

        heightMap.push_back(row);
    }

    print(shortestPath({sStart}, end, heightMap));
    print(shortestPath(starts, end, heightMap));
}
