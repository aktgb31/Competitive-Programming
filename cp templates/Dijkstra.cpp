#include <bits/stdc++.h>
using namespace std;

#define SIZE 100000 + 1

vector<pair<int, int>> v[SIZE];
int dist[SIZE];
bool vis[SIZE];

void dijkstra()
{
    memset(vis, false, sizeof(vis));
    dist[1] = 0;
    multiset<pair<int, int>> s;
    s.insert({0, 1});
    while (!s.empty())
    {
        pair<int, int> p = *s.begin();
        s.erase(s.begin());
        int x = p.second;
        if (vis[x])
            continue;
        for (int i = 0; i < v[x].size(); i++)
        {
            int e = v[x][i].first;
            int w = v[x][i].second;
            if (dist[x] + w < dist[e])
            {
                dist[e] = dist[x] + w;
                s.insert({dist[e], e});
            }
        }
    }
}