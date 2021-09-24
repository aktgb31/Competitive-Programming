/*
  Created by: Amit Kumar at 21:43 on 27 Jun 21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;

#define scan(name, size)           \
    for (int i = 0; i < size; i++) \
        cin >> name[i];
#define print(st, name, size)      \
    for (int i = 0; i < size; i++) \
        st << name[i] << " ";      \
    st << "\n";
#define ll long long
#define S(x, n) memset(x, n, sizeof(x));
#define all(x) x.begin(), x.end()

const long long MAXN = 2e5 + 1;
const long long mod = 1e9 + 7;

template <typename T>
inline istream &operator>>(istream &is, vector<T> &A);
template <class Ch, class Tr, class Container>
inline basic_ostream<Ch, Tr> &operator<<(basic_ostream<Ch, Tr> &os, Container const &x);
template <class X, class Y>
inline ostream &operator<<(ostream &os, pair<X, Y> const &p);

class suffixArrays
{
    int n;
    vector<int> p;
    string &s;
    void sortCyclicShifts()
    {
        const int alphabet = 256;
        vector<int> c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h)
        {
            for (int i = 0; i < n; i++)
            {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
    }

public:
    suffixArrays(string &str) : s(str)
    {
        n = s.size();
        p.resize(n);
        sortCyclicShifts();
    }
    const int &operator[](const int &index)
    {
        return p[index];
    }
};
void solve()
{
    string s;
    cin >> s;
    suffixArrays sa(s);
    for (int i = 0; i < s.size(); i++)
        cout << sa[i] << " ";
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
        cerr << "Case #" << I << ":\n";
#endif
        solve();
    }
#ifdef LOCAL
    auto done = std::chrono::high_resolution_clock::now();
    cerr << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";
#endif
    return 0;
}
template <typename T>
inline istream &operator>>(istream &is, vector<T> &A)
{
    for (int i = 0; i < A.size(); i++)
        is >> A[i];
    return is;
}

template <class Ch, class Tr, class Container>
inline basic_ostream<Ch, Tr> &operator<<(basic_ostream<Ch, Tr> &os, Container const &x)
{
    for (auto &y : x)
        os << y << ' ';
    return os;
}

template <class X, class Y>
inline ostream &operator<<(ostream &os, pair<X, Y> const &p)
{
    return os << p.first << " " << p.second;
}