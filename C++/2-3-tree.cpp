#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>
#include <random>
using namespace std;
#define pii pair<int,int>
#define pnn pair <Node*,Node*>
#define ld long double
#define ll long long
#define ull unsigned long long
#define MOD 1e9
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
struct Node
{
    int max[10];
    vector <Node*> children;
    Node* parent;
    Node(int _val) { max[0] = max[1] = max[2] = max[3]= _val; parent = NULL; }
};
Node* root = NULL;
bool f(Node* a, Node* b)
{
    return a->max[0] < b->max[0];
}
Node* Search(int x)
{
    Node* t = root;
    while (t->children.size() != 0)
    {
        if (t->children.size() == 2)
        {
            if (x > t->max[0])
                t = t->children[1];
            else
                t = t->children[0];
        }
        else if (x > t->max[1])
            t = t->children[2];
        else if (x > t->max[0])
            t = t->children[1];
        else
            t = t->children[0];
    }
    return t;
}
int Max(Node* n)
{
    while (n->children.size() != 0)
    {
        n = n->children[n->children.size() - 1];
    }
    return n->max[0];
}
void Reboot(Node* n)
{
    Node* p = n->parent;
    while (p != NULL)
    {
        for (int i = 0; i < p->children.size()-1; i++)
        {
            p->max[i] = Max(p->children[i]);
        }
        p = p->parent;
    }
}
void Split(Node* n)
{
    if (n->children.size() > 3)
    {
        Node* a = new Node(n->max[2]);
        a->max[0] = n->max[2];
        a->parent = n->parent;
        a->children.push_back(n->children[2]);
        a->children.push_back(n->children[3]);
        n->children[2]->parent = a;
        n->children[3]->parent = a;
        n->children.pop_back();
        n->children.pop_back();
        if (a->parent != NULL)
        {
            a->parent->children.push_back(a);
            sort(a->parent->children.begin(), a->parent->children.end(), f);
            Reboot(a);
            Split(a->parent);
        }
        else
        {
            Node* t = new Node(root->max[0]);
            t->children.push_back(root);
            t->children.push_back(a);
            root->parent = t;
            a->parent = t;
            root = t;
            sort(root->children.begin(), root->children.end(), f);
        }
    }
}
void Insert(int x)
{
    Node* n = new Node(x);
    if (root == NULL)
    {
        root = n;
        return;
    }
    Node* temp = Search(x);
    if (temp->parent == NULL)
    {
        Node* t = new Node(root->max[0]);
        t->children.push_back(root);
        
        t->children.push_back(n);
        root->parent = t;
        n->parent = t;
        root = t;
        sort(root->children.begin(), root->children.end(), f);
    }
    else
    {
        Node* parent = temp->parent;
        parent->children.push_back(n);
        n->parent = parent;
        sort(parent->children.begin(), parent->children.end(), f);
        Reboot(n);
        Split(parent);
    }
    Reboot(n);
}
int H(Node* n,int level)
{
    if(n->children.size()!=0)
    {
        return H(n->children[0], level + 1);
    }
    else
        return level;
}
int p=-1;
void Bypass(Node* n, int level,int h)
{
    if (p == h)
    {
        cout << (char)('A' + level - 1)<<" ";
    }
    p = level;
    fo(i, n->children.size())
    {
        Bypass(n->children[i], level + 1,h);
    }
    if (n->children.size() == 0)
        cout << n->max[0]<<" ";
}
 
int main()
{
    fastio();
    int n, h;
    cin >> n;
    vector <int> a(n);
    fo(i, n)
    {
        cin >> a[i];
        Insert(a[i]);
    }
    h = H(root, 0);
    Bypass(root, 0,h);
}