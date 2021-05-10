/*
  Created by: Amit Kumar at 18:47 on 22 Jan 21
*/
#include <bits/stdc++.h>
#ifdef WIN32
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

vector<pair<int, ll>> adj[MAXN];

const int INF = 1000000000;
vector<ll> dist(MAXN, INF);
vector<bool> vis(MAXN, false);
vector<int> parent(MAXN, -1);
int n, m, k;

void dijkstra(int s)
{
    multiset<pair<ll, int>> q;
    dist[s] = 0;
    q.insert({0, s});
    while (!q.empty())
    {
        db(q);
        pair<ll, int> p = *q.begin();
        q.erase(q.begin());
        int x = p.second;
        ll w = p.first;
        if (vis[x])
            continue;
        vis[x] = true;
        for (auto it : adj[x])
        {
            if (dist[x] + it.second < dist[it.first])
            {
                dist[it.first] = dist[x] + it.second;
                q.insert({dist[it.first], it.first});
                parent[it.first] = x;
            }
        }
    }
}
void restore_path(int s, int t, vector<int> &path)
{

    for (int v = t; v != s; v = parent[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
}
void solve()
{

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        x--;
        y--;
        adj[x].pb(make_pair(y, w));
    }
    dijkstra(0);

    vector<int> path;
    restore_path(0, n - 1, path);
}
int main()
{
#ifdef WIN32
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto started = std::chrono::high_resolution_clock::now();
#endif

#ifndef WIN32
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
    t = 1;
    //cin >> t;
    for (int I = 1; I <= t; I++)
    {
        solve();
    }
#ifdef WIN32
    auto done = std::chrono::high_resolution_clock::now();
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms";
#endif
    return 0;
}