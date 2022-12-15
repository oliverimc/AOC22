#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <regex>

#define print(x) std::cout << x << std::endl

using namespace std;

int minX = INT_MAX, minY = INT_MAX, maxX = -1 * INT_MAX, maxY = -1 * INT_MAX;

void printRanges(vector<pair<int, int>> ranges)
{
    for (auto [b, e] : ranges)
    {
        cout << b << "-" << e << endl;
    }
}

void printPair(pair<int, int> _pair)
{
    cout << _pair.first << ":" << _pair.second << endl;
}

void combineRanges(vector<pair<int, int>> &ranges)
{
    sort(ranges.begin(), ranges.end());

    int toRemove = -1;
    for (int i = 1; i < ranges.size(); i++)
    {
        if (ranges[i - 1].second >= ranges[i].first || (ranges[i].first - ranges[i - 1].second) == 1)
        {
            toRemove = i;
            ranges[i - 1].second = max(ranges[i].second, ranges[i - 1].second);

            break;
        }
    }
    if (toRemove != -1)
    {
        ranges.erase(ranges.begin() + toRemove);
        combineRanges(ranges);
    }
}

int rangesToCount(vector<pair<int, int>> ranges)
{
    int total = 0;
    for (auto [beg, end] : ranges)
    {
        total += end - beg + 1;
    }
    return total;
}

vector<pair<int, int>> getRowRanges(vector<pair<pair<int, int>, pair<int, int>>> _sensorBeaconPairs, set<pair<int, int>> beacons, int rowVal)
{
    vector<pair<int, int>> ranges;
    for (auto [sensor, beacon] : _sensorBeaconPairs)
    {

        int distance = abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);

        if (abs(rowVal - sensor.second) <= distance)
        {
            int rangeStart = sensor.first - (distance - abs(rowVal - sensor.second));
            int rangeEnd = sensor.first + (distance - abs(rowVal - sensor.second));

            if (rangeStart == rangeEnd && beacons.count(make_pair(rangeStart, rowVal)) == 1)
            {
                // pass Don't add beacon posistion single value range
            }
            else
            {
                rangeStart += (beacons.count(make_pair(rangeStart, rowVal)) == 1 ? 1 : 0);
                rangeEnd -= (beacons.count(make_pair(rangeEnd, rowVal)) == 1 ? 1 : 0);
                ranges.push_back(make_pair(rangeStart, rangeEnd));
            }
        }
    }
    return ranges;
}

int main()
{
    ifstream InputFile("day15.txt");
    set<pair<int, int>> beaconPositions; // (row : {cols})
    set<pair<int, int>> sensorPositions;
    vector<pair<pair<int, int>, pair<int, int>>> sensorBeaconPairs;

    for (string line; getline(InputFile, line);)
    {
        regex pointRegex("x=(-?\\d+), y=(-?\\d+)");
        auto regexIt = sregex_iterator(line.begin(), line.end(), pointRegex);
        vector<string> match;
        for (; regexIt != sregex_iterator(); regexIt++)
        {
            for (auto matchStr : *regexIt)
            {
                match.push_back(matchStr);
            }
        }

        pair<int, int> sensor(stoi(match[1]), stoi(match[2]));
        pair<int, int> beacon(stoi(match[4]), stoi(match[5]));

        minX = min(minX, min(sensor.first, beacon.first));
        maxX = max(maxX, max(sensor.first, beacon.first));

        minY = min(minY, min(sensor.second, beacon.second));
        maxY = max(maxY, max(sensor.second, beacon.second));

        beaconPositions.insert(beacon);
        sensorPositions.insert(sensor);

        sensorBeaconPairs.push_back(make_pair(sensor, beacon));
    }

    int rowVal = 2000000; // 2000000;
    int maxVal = 4000000; // 4000000;

    vector<pair<int, int>> ranges = getRowRanges(sensorBeaconPairs, beaconPositions, rowVal);

    combineRanges(ranges);
    print(rangesToCount(ranges));

    for (int row = 0; row < maxVal; row++)
    {

        vector<pair<int, int>> ranges = getRowRanges(sensorBeaconPairs, beaconPositions, row);
        combineRanges(ranges);

        if (ranges.size() > 1)
        {
            for (auto range : ranges)
            {
                pair<long, long> pos(range.second + 1, row);

                if (beaconPositions.count(pos) == 0 && sensorPositions.count(pos) == 0 && pos.first > 0 && pos.first <= maxVal)
                {
                    print(pos.first * maxVal + pos.second);
                }
            }
        }
    }
}
