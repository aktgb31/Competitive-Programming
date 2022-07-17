#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e4 + 5;

int nodes, edges;
pair<long long, pair<int, int>> p[MAX];
int id[MAX], sz[MAX];
void initialize()
{
    for (int i = 0; i < MAX; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}
int root(int x)
{
    while (id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}
void union1(int x, int y)
{
    int p = root(x);
    int q = root(y);
    if (p != q)
    {
        if (sz[p] > sz[q])
            swap(p, q);
        id[p] = id[q];
        sz[q] += sz[p];
    }
}

long long kruskal(pair<long long, pair<int, int>> p[])
{
    initialize();
    int x, y;
    long long cost, minimumCost = 0;
    for (int i = 0; i < edges; i++)
    {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        if (root(x) != root(y))
        {
            minimumCost += cost;
            union1(x, y);
        }
    }
    return minimumCost;
}
int main()
{
    int x, y;
    long long weight, cost, minimumCost;
    initialize();
    cin >> nodes >> edges;
    for (int i = 0; i < edges; i++)
    {
        cin >> x >> y >> weight;
        p[i] = make_pair(weight, make_pair(x, y));
    }
    sort(p, p + edges);
    minimumCost = kruskal(p);
    cout << minimumCost << "\n";
    return 0;
}