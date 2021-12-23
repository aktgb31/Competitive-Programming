#include <bits/stdc++.h>

using namespace std;

// Time Complexity: n*m*
int main()
{
    int n; // person
    int m; // jobs
    vector<vector<int>> adj(n);
    int ans = 0;
    vector<int> match(m + 1, -1);
    vector<bool> seen(m + 1);

    function<bool(int)> isMatchingPossible = [&](int u)
    {
        for (const int &it : adj[u]) // iterating on jobs
        {
            if (!seen[it])
            {
                seen[it] = true;
                if (match[it] < 0 || isMatchingPossible(match[it]))
                {
                    match[it] = u;
                    return true;
                }
            }
        }
        return false;
    };
    for (int i = 0; i < n; i++)
    {
        fill(seen.begin(), seen.end(), false);
        if (isMatchingPossible(i))
            ++ans;
    }
}