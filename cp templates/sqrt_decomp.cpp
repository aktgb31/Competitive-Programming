#include <bits/stdc++.h>
using namespace std;

class sqrtDecomp
{
    int n;
    int len;
    vector<int> arr;
    vector<int> block;
    void preprocess()
    {
        for (int i = 0; i < n; ++i)
            block[i / len] += arr[i];
    }

public:
    sqrtDecomp(int n) : n(n)
    {
        len = (int)sqrt(n + .0) + 1;
        block.resize(len, 0);
        arr.resize(n, 0);
    }

    sqrtDecomp(vector<int> &a)
    {
        arr = a;
        len = (int)sqrt(n + .0) + 1;
        block.resize(len, 0);
        preprocess();
    }

    void update(int idx, int val)
    {
        int blockNumber = idx / n;
        block[blockNumber] += val - arr[idx];
        arr[idx] = val;
    }

    int query(int l, int r)
    {
        int sum = 0;
        int c_l = l / len, c_r = r / len;
        if (c_l == c_r)
            for (int i = l; i <= r; ++i)
                sum += arr[i];
        else
        {
            for (int i = l, end = (c_l + 1) * len - 1; i <= end; ++i)
                sum += arr[i];
            for (int i = c_l + 1; i <= c_r - 1; ++i)
                sum += block[i];
            for (int i = c_r * len; i <= r; ++i)
                sum += arr[i];
        }
        return sum;
    }
};