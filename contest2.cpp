/*
  Created by: Amit Kumar at 11:40 on 10 Jul 22
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;

#define all(x) x.begin(), x.end()

const long long MAXN = 2e5 + 1;
const long long mod = 1e9 + 7;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    db(n, m, k);
    vector<vector<int>> adj(n);
    vector<int> inDeg(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj[x].push_back(y);
        inDeg[y]++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        if (inDeg[i])
        {
            db(i);
            ++ans;
        }
    cout << ans << "\n";
}
int32_t main()
{
#ifdef LOCAL
    freopen("input2.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
    auto started = std::chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    cin >> t;
    for (int I = 1; I <= t; I++)
    {

        cout << "Case #" << I << ": ";

        solve();
    }
#ifdef LOCAL
    auto done = std::chrono::high_resolution_clock::now();
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";
#endif
    return 0;
}