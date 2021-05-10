/*
  Created by: Amit Kumar at 01:15 on 24 Apr 21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;

#define ll long long
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) emplace_back(x)
#define all(x) x.begin(), x.end()
#define NIL -1

const int MAXN = 1e5 + 1;
const long long mod = 1e9 + 7;

int BLOCK;
struct query
{
    int l, r, idx;

    bool operator<(const query &a)
    {
        if (l / BLOCK != a.l / BLOCK)
            return l / BLOCK < a.l / BLOCK;
        return (l / BLOCK & 1) ? (r < a.r) : (r > a.r);
    }
};

struct Mo
{
    static constexpr int MAX_VALUE = 1000001;
    vector<long long> cnt;
    long long current_answer;

    void process(int number, int delta)
    {
        current_answer -= cnt[number] * cnt[number] * number;
        cnt[number] += delta;
        current_answer += cnt[number] * cnt[number] * number;
    }

public:
    Mo()
    {
        cnt = vector<long long>(MAX_VALUE, 0);
        current_answer = 0;
    }

    long long get_answer() const
    {
        return current_answer;
    }

    void add(int number)
    {
        process(number, 1);
    }

    void remove(int number)
    {
        process(number, -1);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    BLOCK = sqrt(n + 0.0) + 1;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<query> queries(q);
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].idx = i;
    }
    sort(all(queries));
    vector<ll> ans(q);

    Mo solver;
    int mo_left = 0, mo_right = -1;
    for (const auto &it : queries)
    {
        while (mo_right < it.r)
        {
            mo_right++;
            solver.add(arr[mo_right]);
        }
        while (mo_right > it.r)
        {
            solver.remove(arr[mo_right]);
            mo_right--;
        }

        while (mo_left < it.l)
        {
            solver.remove(arr[mo_left]);
            mo_left++;
        }
        while (mo_left > it.l)
        {
            mo_left--;
            solver.add(arr[mo_left]);
        }
        ans[it.idx] = solver.get_answer();
    }
    for (auto &it : ans)
        cout << it << "\n";
}
int32_t main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto started = std::chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    //cin >> t;
    for (int I = 1; I <= t; I++)
    {
#ifdef LOCAL
        cerr << "TestCase " << I << "\n";
#endif
        solve();
    }
#ifdef LOCAL
    auto done = std::chrono::high_resolution_clock::now();
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";
#endif
    return 0;
}