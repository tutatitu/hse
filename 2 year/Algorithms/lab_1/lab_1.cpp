#include <iostream>
#include <cmath>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace chrono;
typedef long long ll;
ll _pow(ll a, ll x)
{
    ll ans = 1;
    while (x > 0)
    {
        if (x % 2)
            ans *= a;
        a *= a;
        x = x >> 1;
    }
    return ans;
}
int matrix[8192][8192] = {0}, N = 8192, M, target, tests = 10000;
long long answer_table[2][3][14] = {0};
unordered_map<int, bool (*)()> search;
unordered_map<int, void (*)()> generation;
void First_Generation()
{
    for (int row = 0; row < M; ++row)
    {
        for (int column = 0; column < N; ++column)
            matrix[row][column] = (N / M * row + column) * 2;
    }
}
void Second_Generation()
{
    for (int row = 0; row < N; ++row)
    {
        for (int column = 0; column < N; ++column)
            matrix[row][column] = (N / M * (row + 1) * (column + 1)) * 2;
    }
}
int binary_search(int row, int left, int right)
{
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (matrix[row][middle] == target)
            return middle;
        else if (matrix[row][middle] > target)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return left;
}
bool Binary_Search()
{
    for (int row = 0; row < M; ++row)
    {
        if (matrix[row][binary_search(row, 0, N - 1)] == target)
            return true;
    }
    return false;
}
bool Ladder_Search()
{
    int row = 0, column = N - 1;
    while (row < M && column >= 0)
    {
        if (matrix[row][column] == target)
            return true;
        else if (matrix[row][column] > target)
            column--;
        else
            row++;
    }
    return false;
}
bool Exponential_Search()
{
    int row = 0, column = N - 1;
    while (row < M && column >= 0)
    {
        if (matrix[row][column] == target)
            return true;
        else if (matrix[row][column] > target)
        {
            int step = 1;
            while (column - step >= 0 && matrix[row][column - step] >= target)
                step *= 2;
            column = binary_search(row, max(column - step, 0), column - step / 2);
            if (matrix[row][column] == target)
                return true;
            else
                column--;
        }
        else
            row++;
    }
    return false;
}
int main()
{
    generation[0] = First_Generation;
    generation[1] = Second_Generation;
    search[0] = Binary_Search;
    search[1] = Ladder_Search;
    search[2] = Exponential_Search;
    for (int generation_type = 0; generation_type < 2; ++generation_type)
    {
        for (int search_type = 0; search_type < 3; ++search_type)
        {
            for (int i = 1; i <= 13; ++i)
            {
                M = _pow(2, i);
                generation[generation_type]();
                target = generation_type == 1 ? 16 * N + 1 : 2 * N + 1;
                for (int test = 0; test < tests; ++test)
                {
                    auto start = steady_clock::now();
                    search[search_type]();
                    auto end = steady_clock::now();
                    answer_table[generation_type][search_type][i] += duration_cast<nanoseconds>(end - start).count();
                }
            }
        }
    }
    for (int generation_type = 0; generation_type < 2; ++generation_type)
    {
        if (generation_type == 0)
            cout << "First data type" << endl;
        else
            cout << "Second data type" << endl;
        for (int search_type = 0; search_type < 3; ++search_type)
        {
            if (search_type == 0)
                cout << "Binary Search: ";
            else if (search_type == 1)
                cout << "Ladder Search: ";
            else
                cout << "Exponential Search: ";
            for (int i = 1; i <= 13; ++i)
                cout << answer_table[generation_type][search_type][i] / tests << " ";
            cout << endl;
        }
    }
}