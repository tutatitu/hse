#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <map>
#include <algorithm>
#define ld long double
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fo(i,n) for(int i = 0; i < n; i++)
#define INT_MAX 2147483647
using namespace std;
 
vector <string> list;
map<string, vector <string>> cities;
map<string, pii> coordinates;
map<string, ld> d;
map<string, string> p;
 
int convert(string x)
{
    int ans = 0;
    fo(i, x.size())
    {
        ans = ans * 10 + x[i] - '0';
    }
    return ans;
}
 
ld distance(pii a, pii b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
 
void dij(string x, int n)
{
    // База
    map<string, bool> was;
    for (auto &i : list)
    {
        d[i] = INT_MAX;
        was[i] = false;
        p[i] = "";
    }
    d[x] = 0;
    fo(it,n)
    {
        // Ищем вершину с наименьшим расстоянием
        string x="";
        for (auto &i : list)
        {
            if (!was[i] && (x == "" || d[x] > d[i]))
                x = i;
        }
        // Жадно изменяем расстояние до соседних вершин
        for (auto &e : cities[x])
        {
            if (d[e] > d[x] + distance(coordinates[x], coordinates[e]))
            {
                d[e] = d[x] + distance(coordinates[x], coordinates[e]);
                p[e] = x;
            }
        }
        was[x] = true;
    }
}
 
int main()
{
    int n;
    string start, finish,temp;
    vector <string> path;
    cin >> n;
    int x, y;
    string city, s, neighbour = "";
    cin >> city >> x >> y;
    pii coordinate; coordinate.first = x; coordinate.second = y;
    coordinates[city] = coordinate;
    list.push_back(city);
    while (cin >> temp)
    {
        int flag = 0;
        fo(i,10)
        {
            if (temp[0] - '0' == i)
            {
                flag = 1;
                int y;
                cin >> y;
                string x = *(cities[city].end() - 1);
                list.push_back(x);
                coordinates[x] = pii(convert(temp), y);
                //cout << convert(temp)<<" "<<y << endl;
                cities[city].pop_back();
                city = x;
                break;
            }
        }
        if (flag)
            continue;
        cities[city].push_back(temp);
    }
    finish = *(cities[city].end() - 1); cities[city].pop_back(); start = *(cities[city].end() - 1); cities[city].pop_back();
    
    dij(start, n);
    if (d[finish]==INT_MAX)
    {
        cout << "Path:\n";
        cout << "No way";
        return 0;
    }
    cout << "Path is not greater than ";
    fo(i, 1000000)
    {
        if (d[finish] <= i)
        {
            cout << i<<endl;
            break;
        }
    }
    // Ищем путь пошагово возращаясь назад [Вечное возвращение =)]
    cout << "Path:\n";
    while (finish != "")
    {
        path.push_back(finish);
        finish = p[finish];
    }
    reverse(path.begin(), path.end());
    for (auto city : path)
        cout << city << " ";
}