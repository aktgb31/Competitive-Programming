#include <bits/stdc++.h>
#define NIL -1
#define MAXN 200010
using namespace std;

vector<int> adj[MAXN];
stack<pair<int, int>> st;
bool vis[MAXN];
int disc[MAXN];
int low[MAXN];
int parent[MAXN];
bool ap[MAXN];
void edge(int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void bfs(int u)
{
    queue<int> q;
    q.push(u);
    vis[u] = true;
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (auto i = adj[f].begin(); i != adj[f].end(); i++)
        {
            if (vis[*i] == false)
            {
                q.push(*i);
                vis[*i] = true;
            }
        }
    }
}

void DFS(int u)
{
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); i++)
    {
        if (vis[adj[u][i]] == false)
        {
            DFS(adj[u][i]);
        }
    }
}

void dfs(int v)
{
    memset(vis, false, sizeof(vis));
    for (int u = 0; u < v; u++)
    {
        if (vis[u] == false)
            DFS(u);
    }
}

//Articulation points
void APUtil(int u)
{

    static int time = 0;
    int children = 0;
    vis[u] = true;
    disc[u] = low[u] = ++time;

    for (int i = adj[u][0]; i < adj[u].size(); ++i)
    {
        if (!vis[adj[u][i]])
        {
            children++;
            parent[adj[u][i]] = u;
            APUtil(adj[u][i]);
            low[u] = min(low[u], low[adj[u][i]]);

            if (parent[u] == NIL && children > 1)
                ap[u] = true;

            if (parent[u] != NIL && low[adj[u][i]] >= disc[u])
                ap[u] = true;
        }

        else if (adj[u][i] != parent[u])
            low[u] = min(low[u], disc[adj[u][i]]);
    }
}

void AP(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = NIL;
        vis[i] = false;
        ap[i] = false;
    }

    for (int i = 0; i < n; i++)
        if (vis[i] == false)
            APUtil(i);

    for (int i = 0; i < n; i++)
        if (ap[i] == true)
            cout << i << " ";
}
void bridgeUtil(int u)
{
    static int time = 0;
    vis[u] = true;
    disc[u] = low[u] = ++time;
    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (!vis[v])
        {
            parent[v] = u;
            bridgeUtil(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                cout << u << " " << v << endl;
        }
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

//Bridge detection
void bridge(int V)
{

    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        vis[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (vis[i] == false)
            bridgeUtil(i);
}

//Chechking if there is biconnected component

bool isBCUtil(int u)
{
    static int time = 0;
    int children = 0;
    vis[u] = true;
    disc[u] = low[u] = ++time;

    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (!vis[v])
        {
            children++;
            parent[v] = u;
            if (isBCUtil(v))
                return true;
            low[u] = min(low[u], low[v]);
            if (parent[u] == NIL && children > 1)
                return true;
            if (parent[u] != NIL && low[v] >= disc[u])
                return true;
        }
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
    return false;
}
bool isBC(int V)
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        vis[i] = false;
    }
    if (isBCUtil(0) == true)
        return false;
    for (int i = 0; i < V; i++)
        if (vis[i] == false)
            return false;
    return true;
}

// Biconnected components
int count1 = 0;
void BCCUtil(int u)
{
    static int time = 0;
    disc[u] = low[u] = ++time;
    int children = 0;
    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (disc[v] == -1)
        {
            children++;
            parent[v] = u;
            st.push(make_pair(u, v));
            BCCUtil(v);
            low[u] = min(low[u], low[v]);

            if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
            {
                while (st.top().first != u || st.top().second != v)
                {
                    cout << st.top().first << "--" << st.top().second << " ";
                    st.pop();
                }
                cout << st.top().first << "--" << st.top().second;
                st.pop();
                cout << endl;
                count1++;
            }
        }

        else if (v != parent[u])
        {
            low[u] = min(low[u], disc[v]);
            if (disc[v] < disc[u])
            {
                st.push(make_pair(u, v));
            }
        }
    }
}

void BCC(int V)
{
    for (int i = 0; i < V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        parent[i] = NIL;
    }

    for (int i = 0; i < V; i++)
    {
        if (disc[i] == NIL)
            BCCUtil(i);

        int j = 0;
        while (st.size() > 0)
        {
            j = 1;
            cout << st.top().first << "--" << st.top().second << " ";
            st.pop();
        }
        if (j == 1)
        {
            cout << endl;
            count1++;
        }
    }
}
// Topological sort using DFS
void topologicalSortUtil(int v, stack<int> &st)
{
    vis[v] = true;
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!vis[*i])
            topologicalSortUtil(*i, st);
    st.push(v);
}

void topologicalSort(int V)
{
    stack<int> st;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < V; i++)
        if (vis[i] == false)
            topologicalSortUtil(i, st);

    while (st.empty() == false)
    {
        cout << st.top() << " ";
        st.pop();
    }
}
//using bfs
void topologicalsort(int V)
{
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        vector<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int cnt = 0;
    vector<int> top_order;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
        vector<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        cnt++;
    }
    if (cnt != V)
    {
        cout << "There exists a cycle in the graph\n";
        return;
    }

    // Print topological order
    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i] << " ";
    cout << endl;
}

//KosaRaju's algorithm
vector<int> transpose[MAXN];
vector<int> order, component;

void dfs1(int v)
{
    vis[v] = true;
    for (int i = 0; i < adj[v].size(); ++i)
        if (!vis[adj[v][i]])
            dfs1(adj[v][i]);
    order.push_back(v);
}

void dfs2(int v)
{
    vis[v] = true;
    component.push_back(v);
    for (int i = 0; i < transpose[v].size(); ++i)
        if (!vis[transpose[v][i]])
            dfs2(transpose[v][i]);
}

void connected_components(int n)
{
    s(vis, false);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs1(i);
    }

    s(vis, false);
    for (int i = 0; i < n; i++)
    {
        int v = order[n - 1 - i];
        if (!vis[v])
        {
            dfs2(v);
            for (int j = 0; j < component.size(); j++)
            {
                cout << component[i] << " ";
            }
            cout << "\n";
            component.clear();
        }
    }
}