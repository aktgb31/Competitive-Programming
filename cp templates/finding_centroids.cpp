#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> adj[MAXN];
int sz[MAXN];

int dfs(int n, int u, int prev, vector<int> &centroid)
{
    sz[u] = 1;
    bool is_centroid = true;
    for (auto v : adj[u])
        if (v != prev)
        {
            dfs(n, v, u, centroid);
            sz[u] += sz[v];
            if (sz[v] > n / 2)
                is_centroid = false;
        }
    if (n - sz[u] > n / 2)
        is_centroid = false;
    if (is_centroid)
        centroid.push_back(u);
};

vector<int> Centroid(int n)
{
    vector<int> centroid;

    dfs(n, 0, -1, centroid);
    return centroid;
}

int main()
{
    int n; //number of vertices
    //construct the graph
    auto centroids = Centroid(n);
    if (centroids.size() == 1)
    {
        int c = centroids[0];
    }
    else if (centroids.size() == 2)
    {
        int c1 = centroids[0];
        int c2 = centroids[1];
    }
    else
    {
        assert(false);
    }
    return 0;
}
