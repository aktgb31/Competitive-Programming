/*
  Created by: Amit Kumar at 21:35 on 27 Jun 21
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

void solve()
{
    string pattern, text;
    cin >> pattern >> text;
    string s = pattern + '$' + text;

    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    db(s, pi);
    vector<int> ans;
    for (int i = pattern.size() + 1; i < n; i++)
        if (pi[i] == pattern.size())
            ans.push_back(i - 2 * pattern.size());
    cout << ans;
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