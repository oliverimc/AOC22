#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define print(x) std::cout << x << std::endl

using namespace std;

template <typename T>
void printMatrix(vector<vector<T>> matrix)
{
    for (auto &row : matrix)
    {
        for (auto &character : row)
        {
            cout << character << " ";
        }
        cout << endl;
    }
}

template <typename T>
void resizeMatrix(vector<vector<T>> &matrix, int rows, int cols)
{
    matrix.resize(rows);

    for (auto &row : matrix)
    {
        row.resize(cols);
    }
}

int part1(vector<vector<int>> matrix)
{

    vector<vector<bool>> LRDir, RLDir, TBDir, BTDir; // Masks to indictate what can be seen

    resizeMatrix(LRDir, matrix.size(), matrix[0].size());
    resizeMatrix(RLDir, matrix.size(), matrix[0].size());
    resizeMatrix(TBDir, matrix.size(), matrix[0].size());
    resizeMatrix(BTDir, matrix.size(), matrix[0].size());

    // Left to Right .. Each row go across cols

    for (int r = 0; r < matrix.size(); r++)
    {
        int maxSeen = -1;

        for (int c = 0; c < matrix[0].size(); c++)
        {
            LRDir[r][c] = matrix[r][c] > maxSeen;

            maxSeen = max(matrix[r][c], maxSeen);
        }
    }

    // Right to left .. Each row go across cols

    for (int r = 0; r < matrix.size(); r++)
    {
        int maxSeen = -1;

        for (int c = matrix[0].size() - 1; c >= 0; c--)
        {

            RLDir[r][c] = matrix[r][c] > maxSeen;

            maxSeen = max(matrix[r][c], maxSeen);
        }
    }

    // Top to bottom each column go down rows
    for (int c = 0; c < matrix[0].size(); c++)
    {
        int maxSeen = -1;

        for (int r = 0; r < matrix.size(); r++)
        {
            TBDir[r][c] = matrix[r][c] > maxSeen;

            maxSeen = max(matrix[r][c], maxSeen);
        }
    }

    // Bottom to top each column go down up rows
    for (int c = 0; c < matrix[0].size(); c++)
    {
        int maxSeen = -1;

        for (int r = matrix.size() - 1; r >= 0; r--)
        {
            BTDir[r][c] = matrix[r][c] > maxSeen;

            maxSeen = max(matrix[r][c], maxSeen);
        }
    }

    int number = 0;

    for (int i = 0; i < TBDir.size(); i++)
    {
        for (int j = 0; j < TBDir[0].size(); j++)
        {
            number += TBDir[i][j] || BTDir[i][j] || LRDir[i][j] || RLDir[i][j] ? 1 : 0;
        }
    }
    return number;
}

int neighbours(vector<vector<int>> matrix, int r, int c)
{
    int left = 0, up = 0, down = 0, right = 0;

    for (int li = c - 1; li >= 0; li--)
    {

        left++;
        if (matrix[r][c] <= matrix[r][li])
        {
            break;
        }
    }

    for (int ri = c + 1; ri < matrix[0].size(); ri++)
    {

        right++;
        if (matrix[r][c] <= matrix[r][ri])
        {
            break;
        }
    }

    for (int ui = r - 1; ui >= 0; ui--)
    {

        up++;
        if (matrix[r][c] <= matrix[ui][c])
        {
            break;
        }
    }

    for (int di = r + 1; di < matrix.size(); di++)
    {

        down++;
        if (matrix[r][c] <= matrix[di][c])
        {
            break;
        }
    }

    return up * down * right * left;
}

int part2(vector<vector<int>> matrix)
{
    int maxNeighbours = 1;

    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = 0; c < matrix[0].size(); c++)
        {

            maxNeighbours = max(neighbours(matrix, r, c), maxNeighbours);
        }
    }

    return maxNeighbours;
}

int main()
{

    ifstream InputFile("day8.txt");
    vector<string> input;
    for (string line; getline(InputFile, line);)
    {
        input.push_back(line);
    }

    vector<vector<int>> matrix;
    resizeMatrix(matrix, input.size(), input[0].size());

    for (int r = 0; r < input.size(); r++)
    {
        for (int c = 0; c < input[0].size(); c++)
        {
            matrix[r][c] = int(input[r][c]) - 48;
        }
    }

    print(part1(matrix));
    print(part2(matrix));
}