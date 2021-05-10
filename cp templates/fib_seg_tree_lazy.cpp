#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000009
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAX 300010

ll fb[MAX];
ll fb_pre[MAX];
ll A[MAX];
ll tree[4 * MAX];
pair<int, int> lazy[4 * MAX];
ll combine(ll l, ll r)
{
    return (l + r) % mod;
}
void build(int node, int start, int end)
{
    if (start == end)
        tree[node] = A[start];
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
    lazy[node] = {0, 0};
};
void updaterange(int node, int start, int end, int l, int r)
{
    if (lazy[node] != make_pair(0, 0))
    {
        tree[node] = (tree[node] + fb_pre[end - lazy[node].first + 1] - fb_pre[start - lazy[node].first] + mod) % mod;
        if (start != end)
        {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = make_pair(0, 0);
    }
    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r)
    {
        tree[node] = (tree[node] + fb_pre[end - l + 1] - fb_pre[start - l] + mod) % mod;
        if (start != end)
        {
            lazy[node * 2] = make_pair(l, r);
            lazy[node * 2 + 1] = make_pair(l, r);
        }
        return;
    }
    ll mid = (start + end) / 2;
    updaterange(2 * node, start, mid, l, r);
    updaterange(2 * node + 1, mid + 1, end, l, r);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}
ll queryrange(int node, int start, int end, int l, int r)
{
    if (start > end || start > r || end < l)
    {
        return 0;
    }
    if (lazy[node] != make_pair(0, 0))
    {
        tree[node] = (tree[node] + fb_pre[end - lazy[node].first + 1] - fb_pre[start - lazy[node].first] + mod) % mod;
        if (start != end)
        {
            lazy[node * 2] = make_pair(l, r);
            lazy[node * 2 + 1] = make_pair(l, r);
        }
        lazy[node] = make_pair(0, 0);
    }
    if (start >= l && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    ll p1 = queryrange(2 * node, start, mid, l, r);
    ll p2 = queryrange(2 * node + 1, mid + 1, end, l, r);
    return combine(p1, p2);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }
    build(1, 1, n);
    //cout << tree[1] << " \n";
    while (m--)
    {
        int q, l, r;
        cin >> q >> l >> r;
        if (q == 1)
            updaterange(1, 1, n, l, r);
        else
            cout << queryrange(1, 1, n, l, r) << "\n";
        for (int i = 1; i <= n; i++)
            cout << queryrange(1, 1, n, i, i) << " ";
        cout << "\n";
    }
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
    fb[0] = 0;
    fb[1] = fb[2] = 1;
    fb_pre[0] = 0;
    fb_pre[1] = 1;
    fb_pre[2] = 2;
    for (int i = 3; i < MAX; i++)
    {
        fb[i] = (fb[i - 1] + fb[i - 2]) % mod;
        fb_pre[i] = (fb[i] + fb_pre[i - 1]) % mod;
    }
    int t;
    t = 1;
    //cin >> t;
    for (int I = 1; I <= t; I++)
    {
        solve();
    }
    return 0;
}