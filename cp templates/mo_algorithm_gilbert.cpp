#include <bits/stdc++.h>
using namespace std;

constexpr int logn = 20;
constexpr int maxn = 1 << logn;

long long hilbertOrder(int x, int y)
{
    long long d = 0;
    for (int s = 1 << (logn - 1); s; s >>= 1)
    {
        bool rx = x & s, ry = y & s;
        d = d << 2 | rx * 3 ^ static_cast<int>(ry);
        if (!ry)
        {
            if (rx)
            {
                x = maxn - x;
                y = maxn - y;
            }
            swap(x, y);
        }
    }
    return d;
}

struct Query
{
    int l, r, idx;
    int64_t ord;

    inline void calcOrder()
    {
        ord = hilbertOrder(l, r);
    }
    Query(){};
    Query(int l, int r, int idx)
    {
        this->l = l;
        this->r = r;
        this->idx = idx;
        calcOrder();
    }
    inline bool operator<(const Query &b)
    {
        return this->ord < b.ord;
    }
};
