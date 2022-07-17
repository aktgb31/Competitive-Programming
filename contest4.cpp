/*
  Created by: Amit Kumar at 22:40 on 26 Mar 21
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

void solve()
{
    cout << 1000 << "\n";
    for (int i = 99; i < (1000 * 1001) / 2; i++)
    {
        cout << "100 " << i << "\n";
    }
}
int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto started = std::chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
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
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";
#endif
    return 0;
}