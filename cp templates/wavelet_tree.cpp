#include <bits/stdc++.h>
using namespace std;

class WaveletTree
{
public:
    int low, high;
    WaveletTree *left, *right;
    vector<int> freq;
    typedef vector<int>::iterator itr;

    WaveletTree(itr from, itr to, int l, int r) : low(l), high(r), left(nullptr), right(nullptr)
    {
        if (from == to)
            return;
        if (high == low)
        {
            freq.reserve(high - low + 1);
            freq.push_back(0);
            for (auto it = from; it != to; it++)
                freq.push_back(freq.back() + 1);
            return;
        }
        int mid = (high + low) >> 1;

        auto lessThanMid = [mid](int x) -> bool
        {
            return x <= mid;
        };

        freq.reserve(to - from + 1);
        freq.push_back(0);
        for (auto it = from; it != to; it++)
            freq.push_back(freq.back() + lessThanMid(*it));
        auto pivot = stable_partition(from, to, lessThanMid);

        left = new WaveletTree(from, pivot, low, mid);
        right = new WaveletTree(pivot, to, mid + 1, high);
    }
};