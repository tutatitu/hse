#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <random>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <time.h> 
#include <stack> 
using namespace std;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
#define pnn pair <Node*,Node*>
#define INT_MAX 2147483647
#define LLONG_MAX 9223372036854775807 
#define mod 1000000007
#define p_b push_back
#define fo(i,n) for(int i = 0; i < n; i++)
#define ro(i,n) for(int i = n - 1; i >= 0; i--)
#define fr(i,j,n) for(int i = j; i < n; i++)
#define rf(i,j,n) for(int i=n-1;i>=j;i--)
void fastio()
{
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
}
ull pow_mod(ull a, int x, ull m)
{
    ull ans = 1;
    while (x>0)
    {
        if ((x % 2))
        {
            ans *= a % m;
            ans %= m;
        }
        a *= a;
        a %= m;
        x = x >> 1;
    }
    return ans%m;
}
ull _pow(ull a, ull x)
{
    ull ans = 1;
    while (x > 0)
    {
        if (x % 2)
            ans *= a;
        a *= a;
        x = x >> 1;
    }
    return ans;
}
string ALF = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alf = "abcdefghijklmnopqrstuvwxyz";
//auto begin = chrono::steady_clock::now();
//auto end = chrono::steady_clock::now();
//auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
//cout << "The time: " << elapsed_ms.count() << " ms\n";
 
struct Node
{
    unordered_map<char, Node*> next, go;
    Node* suflink = 0, * parent;
    char pc;
    int h;
    bool terminal = false;
    Node(char _pc, int _h, Node* v)
    {
        pc = _pc;
        parent = v;
        h = _h;
    }
};
 
Node* root = new Node('!', 0, 0);
 
unordered_map<Node*, vector<int>> idx;
 
void add(string& s, int index)
{
    Node* node = root;
    for (char c : s)
    {
        if (!node->next[c])
            node->next[c] = new Node(c, node->h + 1, node);
        node = node->next[c];
    }
    node->terminal = true;
    idx[node].p_b(index);
}
 
Node* go(Node* node, char c);
 
Node* suflink(Node* node)
{
    if (!node->suflink)
    {
        if (node == root || node->parent == root)
            node->suflink = root;
        else
            node->suflink = go(suflink(node->parent), node->pc);
    }
    return node->suflink;
}
 
Node* go(Node* node, char c)
{
    if (!node->go[c])
    {
        if (node->next[c])
            node->go[c] = node->next[c];
        else if (node == root)
            node->go[c] = root;
        else
            node->go[c] = go(suflink(node), c);
    }
    return node->go[c];
}
 
void solve()
{
    int t;
    string S, s;
    vector <int> ans[1000001];
    cin >> S >> t;
    fo(i, t)
    {
        cin >> s;
        add(s, i);
    }
    Node* v = root;
    for (int i = 0; i != S.size(); i++)
    {
        v = go(v, S[i]);
        Node* node = v;
        while (node != root)
        {
            if (node->terminal)
            {
                for (int x : idx[node])
                    ans[x].p_b(i - node->h + 2);
            }
            node = suflink(node);
        }
    }
    fo(i, t)
    {
        cout << ans[i].size();
        for (int x : ans[i])
            cout << " " << x;
        cout << endl;
    }
}
 
int main()
{
    fastio();
    solve();
}