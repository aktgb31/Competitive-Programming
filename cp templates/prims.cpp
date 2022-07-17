#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e4 + 5;
#define ll long long

typedef pair<ll, int> pii;
bool vis[MAX];
vector<pii> adj[MAX];

ll prim(int x)
{
    priority_queue<pii, vector<pii>, greater<pii>> q;
    int y;
    ll minCost = 0;
    pii p;
    q.push(make_pair(0, x));
    while (!q.empty())
    {
        p = q.top();
        q.pop();
        x = p.second;
        if (vis[x] == true)
            continue;
        minCost += p.first;
        vis[x] = true;
        for (int i = 0; i < adj[x].size(); i++)
        {
            y = adj[x][i].second;
            if (vis[y] == false)
                q.push(adj[x][i]);
        }
    }
    return minCost;
}

int main()
{
    int nodes, edges, x, y;
    ll weight, minCost;
    cin >> nodes >> edges;
    for (int i = 0; i < edges; i++)
    {
        cin >> x >> y >> weight;
        adj[x].push_back(make_pair(weight, y));
        adj[y].push_back(make_pair(weight, x));
    }
    minCost = prim(1);
    cout << minCost << "\n";
    return 0;
}