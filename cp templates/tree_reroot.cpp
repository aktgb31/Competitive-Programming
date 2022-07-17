/*
  Created by: Amit Kumar at 00:33 on 04 Feb 21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;
#define int long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define all(x) x.begin(), x.end()
#define NIL -1
const int MAXN = 1e5 + 1;

void calculatedp(int u, int p, vector<int> &dp, vector<int> &subtree, vector<vector<int>> &adj)
{
    subtree[u] = 1;
    for (auto it : adj[u])
    {
        if (it != p)
        {
            calculatedp(it, u, dp, subtree, adj);
            subtree[u] += subtree[it];
            dp[u] += dp[it];
        }
    }
    dp[u] += subtree[u];
}
void reroot(int u, int p, vector<int> &dp, vector<int> &subtree, vector<vector<int>> &adj, int &ans)
{
    ans = max(ans, dp[u]);
    for (auto it : adj[u])
    {
        if (it == p)
            continue;
        //Disconnecting it from u
        dp[u] -= subtree[it];
        dp[u] -= dp[it];
        subtree[u] -= subtree[it];

        //Appending u to it
        subtree[it] += subtree[u];
        dp[it] += subtree[u];
        dp[it] += dp[u];

        reroot(it, u, dp, subtree, adj, ans);

        //Undo the rerooting
        dp[it] -= dp[u];
        dp[it] -= subtree[u];
        subtree[it] -= subtree[u];

        subtree[u] += subtree[it];
        dp[u] += dp[it];
        dp[u] += subtree[it];
    }
}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n, 0);
    vector<int> subtree(n, 0);
    calculatedp(0, -1, dp, subtree, adj);
    int ans = 0;
    reroot(0, -1, dp, subtree, adj, ans);
    cout << ans << "\n";
}
signed main()
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