#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define s(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 40005

int tree[4 * MAXN], lazy[4 * MAXN];

void update(int node, int start, int end, int l, int r, int p)
{
    if (lazy[node] != 0)
    {
        tree[node] = lazy[node];
        if (start != end)
        {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r)
    {
        tree[node] = p;
        if (start != end)
        {
            lazy[node * 2] = p;
            lazy[node * 2 + 1] = p;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, p);
    update(2 * node + 1, mid + 1, end, l, r, p);
    tree[node] = p;
}

int query(int node, int start, int end, int l, int r)
{
    if (lazy[node] != 0)
    {
        tree[node] = lazy[node];
        if (start != end)
        {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > r || end < l)
    {
        return 0;
    }
    if (start >= l && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}
void solve()
{
    s(tree, 0);
    s(lazy, 0);
    pair<int, int> range[MAXN];
    int n;
    cin >> n;
    set<int> vis;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l;
        cin >> r;
        // cout << l << " " << r << "\n";
        range[i].first = l;
        range[i].second = r;
        vis.insert(l);
        vis.insert(r);
    }
    map<int, int> compress;
    int j = 1;
    for (auto it = vis.begin(); it != vis.end(); it++)
    {
        compress[*it] = (j);
        // cout << "j " << j << " "
        //     << "val= " << (*it) << "\n";
        j++;
    }
    //cout << vis.size() << "\n";
    for (int i = 0; i < n; i++)
    {
        update(1, 1, vis.size(), compress[range[i].first], compress[range[i].second], i + 1);
    }
    set<int> ans;
    for (int i = 1; i <= vis.size(); i++)
    {
        int x = query(1, 1, vis.size(), i, i);
        //  cout << "x= " << x << "\n";
        ans.insert(x);
    }
    ans.erase(0);
    cout << ans.size() << "\n";
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
    cin >> t;
    for (int I = 1; I <= t; I++)
    {
        solve();
    }
    return 0;
}