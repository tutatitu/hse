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
#define pnn pair<Node*,Node*>
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
	Node* l=NULL;
	Node* r=NULL;
	int val, priority;
	Node(int _val) { val = _val, priority = rand(); }
};
Node* root = NULL;
Node* Merge(Node* l, Node* r)
{
	if (l==NULL)
		return r;
	if (r==NULL)
		return l;
	if (l->priority < r->priority)
	{
		l->r = Merge(l->r, r);
		return l;
	}
	else
	{
		r->l = Merge(l,r->l);
		return r;
	}
}
pnn Split(Node* n, int x)
{
	if (n == NULL)
		return {NULL,NULL};
	if (n->val < x)
	{
		pnn p = Split(n->r, x);
		n->r = p.first;
		return { n,p.second };
	}
	else
	{
		pnn p = Split(n->l, x);
		n->l = p.second;
		return { p.first,n };
	}
}
void Insert(int x)
{
	pnn p = Split(root, x);
	Node* t = new Node(x);
	root = Merge(p.first, Merge(t, p.second));
}
int a = -1;
int Lower(Node* n,int x)
{
	if (n == NULL)
		return a;
	if (n->val == x)
	{
		return x;
	}
	if (n->val > x)
	{
		a = n->val;
		return Lower(n->l, x);
	}
	return Lower(n->r, x);
}
int main()
{
	fastio();
	int t,n=0;
	string prev = "+";
	cin >> t;
	while (t--)
	{
		int x;
		string command;
		cin >> command>>x;
		if(command=="?")
		{
			n = Lower(root, x);
			cout << n<<endl;
			prev = "?";
			a = -1;
		}
		else
		{
			if (prev == "?")
			{
				Insert((x + n)%(int)MOD);
			}
			else
				Insert(x);
			prev = "+";
		}
	}
}