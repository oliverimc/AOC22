#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define print(x) std::cout << x << std::endl

using namespace std;

void systemCycle(int &cycle, int X, int &signal)
{

	if (cycle % 40 == 0 && cycle != 0)
	{
		cout << endl;
	}
	cout << (abs(cycle % 40 - X) < 2 ? "#" : ".");
	cycle++;
	signal += (cycle - 20) % 40 == 0 ? cycle * X : 0;
}

int main()
{

	ifstream InputFile("day10.txt");
	int cycle = 0, X = 1, signal = 0;
	map<int, int> toAdd;

	for (string cmd; getline(InputFile, cmd);)
	{
		if (cmd == "noop")
		{
			systemCycle(cycle, X, signal);
		}

		else
		{
			int addValue = stoi(cmd.substr(4, cmd.size()));

			systemCycle(cycle, X, signal);
			systemCycle(cycle, X, signal);

			X += addValue;
		}
	}

	print(" ");
	print(signal);
}