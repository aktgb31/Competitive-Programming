#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 4000010
string s;
struct d
{
    int t;
    int s;
    int e;
};

d tree[MAXN];
d combine(d a, d b)
{
    d temp;
    int t = min(a.s, b.e);
    temp.t = a.t + b.t + t;
    temp.s = a.s + b.s - t;
    temp.e = a.e + b.e - t;
    return temp;
}
void build(int node, int l, int r)
{
    if (l == r)
    {

        tree[node].s = s[l] == '(' ? 1 : 0;
        tree[node].e = s[l] == ')' ? 1 : 0;
        tree[node].t = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
}
d query(int node, int l, int r, int start, int end)
{
    if (l > r || r < start || l > end)
    {
        return {0, 0, 0};
    }
    if (l <= start && r >= end)
        return tree[node];
    int mid = (start + end) / 2;
    d p1 = query(2 * node, l, r, start, mid);
    d p2 = query(2 * node + 1, l, r, mid + 1, end);
    return combine(p1, p2);
}
void solve()
{
    //S(tree, 0);
    cin >> s;
    int n = s.size();
    s = " " + s;
    //cout << s << "\n";
    build(1, 1, n);
    int m;
    cin >> m;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        cout << 2 * query(1, x, y, 1, n).t << "\n";
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
    int t;
    t = 1;
    /// cin >> t;
    for (int I = 1; I <= t; I++)
    {
        solve();
    }
    return 0;
}