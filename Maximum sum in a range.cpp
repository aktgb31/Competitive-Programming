#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define s(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)

struct s
{
    ll pre;
    ll suff;
    ll sum;
    ll ans;
};
int A[50010];
s tree[200040];
s init(ll x)
{
    s res;
    res.sum = x;
    res.pre = res.suff = res.ans = max((ll)0, x);
    return res;
}
s combine(s l, s r)
{
    s res;
    res.sum = l.sum + r.sum;
    res.pre = max(l.pre, l.sum + r.pre);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pre);
    return res;
}
void build(int node, int start, int end)
{
    if (start == end)
        tree[node] = init(A[start]);
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}
void update(int node, int start, int end, int idx)
{
    if (start == end)
    {
        tree[node] = init(A[start]);
    }
    else
    {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update(2 * node, start, mid, idx);
        else
            update(2 * node + 1, mid + 1, end, idx);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}
s query(int node, int start, int end, int l, int r)
{
    if (r < start || l > end)
        return init(0);
    if (l <= start && r >= end)
        return tree[node];
    int mid = (start + end) / 2;
    s p1 = query(2 * node, start, mid, l, r);
    s p2 = query(2 * node + 1, mid + 1, end, l, r);
    return combine(p1, p2);
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
    ll n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    // cout << n;
    build(1, 1, n);
    ll q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        s res = query(1, 1, n, l, r);
        cout << res.ans << "\n";
    }

    return 0;
}