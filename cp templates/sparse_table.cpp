#include <bits/stdc++.h>
using namespace std;

template <typename inpType, int (*func)(int, int)>
struct sparse_table
{
    int n, logLim, def;
    vector<vector<int>> lookup;
    vector<int> Log2;
    sparse_table(vector<inpType> arr, int def = 0)
    {
        this->n = arr.size();
        this->def = def;

        Log2.resize(n + 1, 0);
        for (int i = 2; i <= n; i++)
            Log2[i] = Log2[i / 2] + 1;

        logLim = Log2[n] + 1;
        lookup.resize(n, vector<int>(logLim, def));
        for (int i = 0; i < n; i++)
        {
            lookup[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
            {
                lookup[i][j] = func(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
            }
    }

    int query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = Log2[R - L + 1];
        return func(lookup[L][j], lookup[R - (1 << j) + 1][j]);
    }
};
