/*
  Created by: Amit Kumar at 13:17 on 13 Dec 20
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 11

void modInverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        printf("Inverse doesn't exist");
    else
    {
        // m is added to handle negative x
        int res = (x % m + m) % m;
        printf("Modular multiplicative inverse is %d", res);
    }
}

tuple<int, int, int> extended_gcd(int a, int b)
{
    if (a == 0)
        return make_tuple(b, 0, 1);

    int gcd, x, y;

    // unpack tuple  returned by function into variables
    tie(gcd, x, y) = extended_gcd(b % a, a);

    return make_tuple(gcd, (y - (b / a) * x), x);
}

void solve()
{
    int a = 442;
    int b = 147;

    tuple<int, int, int> t = extended_gcd(a, b);

    int gcd = get<0>(t);
    int x = get<1>(t);
    int y = get<2>(t);

    cout << "GCD is " << gcd << endl;
    cout << "x = " << x << " y = " << y << endl;

    cout << a << "*" << x << " + " << b << "*" << y << " = " << gcd;
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