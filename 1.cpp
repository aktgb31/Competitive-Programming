#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define re(in, n) for (ll i = in; i < n; i++)
#define v(x) vector<int> x;
#define all(x) x.begin(), x.end()
#define s(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#ifndef ONLINE_JUDGE
void debug()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
#endif
template <typename t>
void db(const vector<t> &temp)
{
    for (int i = 0; i < temp.size(); i++)
        cerr << temp[i] << " ";
    cerr << "\n";
}
template <typename t>
inline void sfast(t &x)
{
    register int c = getchar();
    x = 0;
    int neg = 0;

    for (; ((c < 48 || c > 57) && c != '-'); c = getchar())
        ;

    if (c == '-')
    {
        neg = 1;
        c = getchar();
    }

    for (; c > 47 && c < 58; c = getchar())
    {
        x = (x << 1) + (x << 3) + c - 48;
    }
    if (neg)
        x = -x;
}
template <typename t>
bool isp2(t x)
{
    return (x && !(x & (x - 1)));
}
template <typename t1, typename t2>
t1 power(t1 x, t2 y)
{
    t1 res = 1;
    x = x % mod;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % mod;
        y = y >> 1;
        x = (x * x) % mod;
    }
    return res;
}
template <typename t>
t gcd(t m, t n)
{
    if (n == 0)
        return m;
    else
        return gcd(n, m % n);
}
template <typename t>
bool isprime(t n)
{
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
using namespace std;
int main()
{
    fast int t = 1;
    while (t--)
    {
    }
    return 0;
}
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};