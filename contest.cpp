/*
  Created by: Amit Kumar at 02:44 on 10 May 21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;

#define ll long long
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) emplace_back(x)
#define all(x) x.begin(), x.end()
#define NIL -1

const long long MAXN = 1e5 + 1;
const long long mod = 1e9 + 7;

template <typename T>
istream &operator>>(istream &is, vector<T> &A);

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    map<char, int> mp;
    for (int i = 0; i < n; i++)
    {
        mp[s[i]]++;
    }
    vector<int> size;
    for (auto &[u, v] : mp)
    {
        size.push_back(v);
    }
    sort(all(size), greater<int>());
    db(size);
    int ans = 1;
    for (int i = 1; i <= k; i++)
    {
        if (k % i == 0 && i <= size.size())
        {
            ans = max(ans, size[i - 1] * i);
        }
    }
    cout << ans << "\n";
}
int32_t main()
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
    cin >> t;
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
template <typename T>
istream &operator>>(istream &is, vector<T> &A)
{
    for (int i = 0; i < A.size(); i++)
        is >> A[i];
    return is;
}