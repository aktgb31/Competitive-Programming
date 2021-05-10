#include <bits/stdc++.h>
#define ll long long int
#define M 1000000007
#define mod 998244353
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define pi pair<ll, ll>
#define endl "\n"
using namespace std;
const ll N = 500010;
#include "debug.h"
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t;
    cin >> t;
    while (t--)
    {
        ll k, n, l, r;
        cin >> k >> n >> l >> r;
        vector<ll> ar[k];
        for (ll i = 0; i < k; ++i)
        {
            for (ll j = 0; j < n; ++j)
            {
                ll x;
                cin >> x;
                ar[i].pb(x);
            }
            sort(ar[i].begin(), ar[i].end());
        }

        ll st = 0, en = n, mid, ans;
        while (st <= en)
        {
            mid = (st + en) / 2;

            ll left, right;
            for (ll i = 0; i < k; ++i)
            {
                ll minsum = 0, maxsum = 0;
                for (ll j = 0; j < n; ++j)
                {
                    if (j < mid)
                    {
                        maxsum += r;
                    }
                    else
                    {
                        maxsum += ar[i][j];
                    }
                }
                ll counter = 0;
                for (ll j = n - 1; j >= 0; --j)
                {
                    if (counter < mid)
                    {
                        minsum += l;
                    }
                    else
                    {
                        minsum += ar[i][j];
                    }
                    ++counter;
                }

                if (i == 0)
                {
                    left = minsum;
                    right = maxsum;
                }
                else
                {
                    left = max(left, minsum);
                    right = min(right, maxsum);
                }
            }

            if (left <= right)
            {
                ans = mid;
                en = mid - 1;
            }
            else
            {
                st = mid + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
