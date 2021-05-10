#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define mp make_pair
#define fi first
#define se second
#define pii pair<int, int>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define ppi pair<pii, pii>
#define vi vector<int>
#define vl vector<ll>
#define uset unordered_set
#define umap unordered_map
#define INF (1 << 30)
#define INF_LL (1ll << 60)
#define MAX 2000005
#define MAX_LVL 21

using namespace std;

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &V);

template <typename T>
ostream &operator<<(ostream &out, const set<T> &S);

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &P);

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const map<T1, T2> &M);

int find_first_num_index(ll &k, ll n)
{
    if (n == 1)
    {
        return 0;
    }
    n--;

    int first_num_index;
    ll n_partial_fact = n;

    while (k >= n_partial_fact && n > 1)
    {
        n_partial_fact *= (n - 1);
        n--;
    }

    first_num_index = k / n_partial_fact;
    k %= n_partial_fact;

    return first_num_index;
}

vector<int> find_kth_permutation(ll n, ll k)
{
    vector<int> Ans;
    set<int> S;

    for (int i = 1; i <= n; i++)
    {
        S.insert(i);
    }

    auto itr = S.begin();
    k -= 1;

    for (int i = 0; i < n; i++)
    {
        int index = find_first_num_index(k, n - i);
        advance(itr, index);
        Ans.push_back((*itr));
        S.erase(itr);
        itr = S.begin();
    }

    return Ans;
}

void testcase()
{
    int n, q;
    cin >> n >> q;
    int suff_len = min(14, n);
    int pref_len = n - suff_len;
    ll x = 1;
    ll Sil[20];
    Sil[0] = 1;
    vector<int> Suf = find_kth_permutation(suff_len, 1);
    for (int i = 1; i <= suff_len; i++)
    {
        Sil[i] = Sil[i - 1] * i;
    }
    for (int h = 0; h < q; h++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            ll ans = 0;
            int r_pr = min(r, pref_len);
            if (l <= r_pr)
            {
                ans += 1ll * (l + r_pr) * (r_pr - l + 1) / 2; // Arithmetic sum
            }
            r -= pref_len + 1;
            l -= pref_len + 1;
            r_pr = max(r_pr - pref_len - 1, 0);
            for (int i = max(l, 0); i <= r; i++)
            {
                ans += pref_len + Suf[i]; // Rest of elements
            }
            cout << ans << endl;
        }
        else
        {
            int dx;
            cin >> dx;
            x += dx;
            x = min(x, Sil[suff_len]);
            Suf = find_kth_permutation(suff_len, x);
            cerr << Suf << endl;
        }
    }
}

void init()
{
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    init();
    int T = 1;
    //cin >> T;
    for (int t = 1; t <= T; t++)
    {
        testcase();
    }
    return 0;
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &V)
{
    if (!V.empty())
    {
        out << "{";
        for (auto v : V)
            out << v << ", ";
        out << "\b\b}"; // \b is backspace
    }
    else
    {
        out << "{}";
    }
    return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &S)
{
    if (!S.empty())
    {
        out << "set{";
        for (auto v : S)
            out << v << ", ";
        out << "\b\b}"; // \b is backspace
    }
    else
    {
        out << "{}";
    }
    return out;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const map<T1, T2> &M)
{
    if (!M.empty())
    {
        out << "map{";
        for (auto &kv : M)
            out << "(" << kv.fi << ": " << kv.se << ")"
                << ", ";
        out << "\b\b}"; // \b is backspace
    }
    else
    {
        out << "{}";
    }
    return out;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &P)
{
    out << "{" << P.first << ", " << P.second << "}";
    return out;
}