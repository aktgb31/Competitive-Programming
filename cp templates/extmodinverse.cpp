/*
  Created by: Amit Kumar at 15:23 on 13 Dec 20
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 11
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}
int modInverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g == 1)
    {
        int res = (x % m + m) % m;
        return res;
    }
};
void solve()
{
}
int main()
{
#ifdef WIN32
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
    return 0;
}