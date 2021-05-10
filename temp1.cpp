/*
  Created by: Amit Kumar at 01:49 on 10 Jan 21
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 11

set<string> st;
bool check(char &c)
{
    return c == ' ';
}
void solve()
{
    string s;
    while (getline(cin, s))
    {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        st.insert(s);
    }
    for (auto it : st)
        cout << "\"" << it << "\""
             << ",\n";
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
    //cin >> t;
    for (int I = 1; I <= t; I++)
    {
        solve();
    }
    return 0;
}