#include <bits/stdc++.h>
using namespace std;

// Time complexity: Vertex *(edge *edge)

class edmonds_karp
{
private:
    static constexpr int INF = numeric_limits<int>::max();
    vector<vector<int>> capacity;
    const int n;
    const vector<vector<pair<int, int>>> &graph;

    int bfs(int s, int t, vector<int> &parent)
    {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INF});

        while (!q.empty())
        {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (auto &[next, cap] : graph[cur])
            {
                if (parent[next] == -1 && capacity[cur][next])
                {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

public:
    edmonds_karp(vector<vector<pair<int, int>>> &adj) : graph(adj), n(adj.size()) // add reverse edges with weight 0 too
    {
        capacity.assign(n, vector<int>(n, 0));
        for (int from = 0; from < n; from++)
            for (auto &[to, cap] : adj[from])
                capacity[from][to] = cap;
    }

    int maxFlow(int source, int sink)
    {
        int flow = 0;
        vector<int> parent(n);
        int new_flow;

        while (new_flow = bfs(source, sink, parent))
        {
            flow += new_flow;
            int cur = sink;
            while (cur != source)
            {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }
};
