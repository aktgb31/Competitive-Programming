#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 11

ll power(ll x, unsigned ll y)
{
    ll res = 1; // Initialize result
    x %= mod;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % mod;
        y = y >> 1;
        x = (x * x) % mod;
    }
    return res;
}

ll modInverse(ll n)
{
    return power(n, mod - 2);
}
ll nCrModPFermat(unsigned ll n,
                 ll r)
{
    if (n < r)
        return 0;
    if (r == 0)
        return 1;

    unsigned ll fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % mod;

    return (fac[n] * modInverse(fac[r]) % mod * modInverse(fac[n - r]) % mod) % mod;
}
