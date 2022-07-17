/*
  Created by: Amit Kumar at 15:02 on 17 Feb 21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define all(x) x.begin(), x.end()
#define NIL -1
const int MAXN = 1e5 + 1;
const int LOG = 20;

vector<vector<pair<int, int>>> adj(MAXN);
vector<vector<int>> parent(MAXN, vector<int>(LOG, -1)), maxw(MAXN, vector<int>(LOG, INT_MIN)), minw(MAXN, vector<int>(LOG, INT_MAX));
vector<int> levels(MAXN);

void dfs(int u, int p = -1, int dist = 0, int level = 1)
{
    parent[u][0] = p;
    maxw[u][0] = dist;
    minw[u][0] = dist;
    levels[u] = level;
    for (int i = 1; i < LOG; i++)
    {
        if (parent[u][i - 1] != -1)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
            maxw[u][i] = max(maxw[u][i - 1], maxw[parent[u][i - 1]][i - 1]);
            minw[u][i] = min(minw[u][i - 1], minw[parent[u][i - 1]][i - 1]);
        }
    }

    for (auto it : adj[u])
    {
        if (it.first != p)
        {
            dfs(it.first, u, it.second, level + 1);
        }
    }
}

void lca(int u, int v)
{
    int minWei = INT_MAX;
    int maxWei = INT_MIN;

    if (levels[u] > levels[v])
        swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
    {

        if (parent[v][i] != -1 && levels[parent[v][i]] >= levels[u])
        {
            minWei = min(minWei, minw[v][i]);
            maxWei = max(maxWei, maxw[v][i]);
            v = parent[v][i];
        }
    }
    db(u, v);
    if (v == u)
    {
        cout << minWei << " " << maxWei << "\n";
        return;
    }
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (parent[u][i] != -1 && parent[v][i] != parent[u][i])
        {
            minWei = min(minWei, min(minw[v][i], minw[u][i]));
            maxWei = max(maxWei, max(maxw[v][i], maxw[u][i]));

            v = parent[v][i];
            u = parent[u][i];
        }
    }
    db(u, v);
    minWei = min(minWei, min(minw[v][0], minw[u][0]));
    maxWei = max(maxWei, max(maxw[v][0], maxw[u][0]));
    cout << minWei << " " << maxWei << "\n";
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(0);
    // db(parent);
    // db(levels);
    int m;
    cin >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        lca(u, v);
    }
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto started = std::chrono::high_resolution_clock::now();
#endif

#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
    t = 1;
    //cin >> t;
    for (int I = 1; I <= t; I++)
    {
#ifdef LOCAL
        cerr << "TestCase " << I << "\n";
#endif
        solve();
    }
#ifdef LOCAL
    auto done = std::chrono::high_resolution_clock::now();
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms";
#endif
    return 0;
}