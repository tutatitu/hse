#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

int Distance(pair<int, int> point, pair<int, int> point1, pair<int, int> point2)
{
    return (point.first - point1.first) * (point2.second - point1.second) - (point.second - point1.second) * (point2.first - point1.first);
}
 
vector <pair<int, int>> points;
set <pair<int, int>> convex_hull;
 
void Convex_Hull(pair <int,int> point1, pair <int, int> point2, int side)
{
    int i,max=0,idx=INT_MIN;
    for (i = 0; i < points.size(); i++)
    {
        if (abs(Distance(points[i], point1, point2)) > max && Distance(points[i], point1, point2) * side > 0)
        {
            max = abs(Distance(points[i], point1, point2));
            idx = i;
        }
    }
    //cout << "9";
    if (idx == INT_MIN)
    {
        convex_hull.insert(point1);
        convex_hull.insert(point2);
        return;
    }
    Convex_Hull(point1, points[idx], side);
    Convex_Hull(points[idx],point2, side);
}
 
int main()
{
    int x, y, i, min_x = 0, max_x = 0,counter=0;
    string str;
    pair<int, int> temp;
    while (scanf("%d%d",&x,&y)!=EOF)
    {
        temp.first=x;temp.second=y;
        points.push_back(temp);
    }
    for (i = 0; i < points.size(); i++)
    {
        if (points[i].first > points[max_x].first)
        {
            max_x = i;
        }
        if (points[i].first < points[min_x].first)
        {
            min_x = i;
        }
    }
    Convex_Hull(points[min_x], points[max_x], 1);
    Convex_Hull(points[min_x], points[max_x], -1);
    cout << "Convex Hull is:\n";
    for (auto x : convex_hull)
    {
        if (counter == convex_hull.size() - 1)
        {
            cout << x.first << " " << x.second;
            return 0;
        }
        cout << x.first << " " << x.second << endl;
        counter++;
    }
}