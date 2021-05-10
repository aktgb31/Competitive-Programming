/*
  Created by: Amit Kumar at 01:36 on 10 Jan 21
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define S(x, n) memset(x, n, sizeof(x));
#define pb(x) push_back(x)
#define NIL -1
#define MAXN 11
#include "debug.h"

vector<string> arr = {
    "b200841cs",
    "b200209ee",
    "b200738",
    "200054",
    "200046",
    "200219",
    "200316",
    "200739",
    "200843",
    "200795",
    "200709",
    "200477",
    "200704",
    "200798",
    "200894",
    "200745",
    "200755",
    "200956",
    "201007",
    "m190718cs",
    "170837",
    "180533",
    "180467",
    "180511",
    "180608",
    "180603",
    "180911",
    "180457",
    "180628",
    "b190436",
    "190828",
    "190277", "190875", "190764", "191107", "190331", "191046", "190187",
    "190839", "191058", "190157"};

void solve()
{
    cerr << arr.size() << "\n";
    vector<bool> vis(41, false);
    // for (auto it : arr)
    // {
    //     cout << it << "\n";
    // }
    // cout << arr.size() << "\n";
    string s;
    while (getline(cin, s))
    {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        for (int i = 0; i < arr.size(); i++)
        {
            string it = arr[i];
            int k = s.find(it);
            if (k != string::npos)
            {
                vis[i] = true;
                cout << s << "\n";
                break;
            }
        }
    }
    db(vis);
}
int main()
{
#ifdef WIN32
    freopen("ranklist.csv", "r", stdin);
    freopen("final_result.csv", "w", stdout);
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