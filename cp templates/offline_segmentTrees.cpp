#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define s(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 30010

int tree[4 * MAXN];
bool comp1(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first > b.first;
}
bool comp2(const pair<pair<int, int>, pair<int, int>> &a, const pair<pair<int, int>, pair<int, int>> &b)
{
    return a.first.first > b.first.first;
}
void update(int node, int start, int end, int idx)
{
    if (start == end)
    {
        tree[node] = 1;
    }
    else
    {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update(2 * node, start, mid, idx);
        else
            update(2 * node + 1, mid + 1, end, idx);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}
int query(int node, int start, int end, int l, int r)
{
    if (r < start || l > end)
        return 0;
    if (l <= start && r >= end)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}
void solve()
{
    s(tree, 0);
    int n;
    cin >> n;
    pair<int, int> arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].first;
        arr[i].second = i + 1;
    }
    //    cout << n << "\n";
    sort(arr, arr + n, comp1);
    int m;
    cin >> m;
    pair<pair<int, int>, pair<int, int>> range[m];
    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        range[i].first.first = k;
        range[i].first.second = i;
        range[i].second.first = l;
        range[i].second.second = r;
    }
    sort(range, range + m, comp2);
    int j = 0;
    //  cout << m << "\n";
    int ans[m];
    for (int i = 0; i < m; i++)
    {
        while (range[i].first.first < arr[j].first)
        {
            update(1, 1, n, arr[j].second);
            j++;
        }
        ans[range[i].first.second] = query(1, 1, n, range[i].second.first, range[i].second.second);
    }
    for (int i = 0; i < m; i++)
    {
        cout << ans[i] << "\n";
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