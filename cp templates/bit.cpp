#include <bits/stdc++.h>
using namespace std;
struct FenwickTree
{
    vector<int> bit; // binary indexed tree
    int n;

    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(const vector<int> &a) : FenwickTree(a.size())
    {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r)
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r)
    {
        if (l == 0)
            return sum(r);
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

template <typename T>
struct BIT
{

    int size;
    vector<T> bit;
    BIT(int size)
    {
#ifndef ONLINE_JUDGE
        cerr << "This is 1 based noob, don't forget\n"
#endif
            ;
        this->size = size + 1;
        bit.assign(this->size, 0);
    }
    void update(int i, T delta)
    {
        while (i < size)
        {
            bit[i] += delta;
            i = i + (i & (-i));
        }
    }
    T sum(int i)
    {
        T ret = 0;
        while (i > 0)
        {
            ret += bit[i];
            i = i - (i & (-i));
        }
        return ret;
    }
    T rangeSum(int i, int j)
    {
        if (i == 0)
            return sum(j);
        return sum(j) - sum(i - 1);
    }
    void print()
    {
        for (int i = 0; i < size; i++)
            cout << rangeSum(i, i) << ' ';
    }
};

///////////////

const int NNN = 1e5;
struct RangeBit
{
    int data[NNN];
    void update(int idx, int val)
    {
        while (idx < NNN)
        {
            data[idx] += val;
            idx += idx & (-idx);
        }
    }
    void update(int l, int r, int val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    int query(int idx)
    {
        int res = 0;
        while (idx > 0)
        {
            res += data[idx];
            idx -= idx & (-idx);
        }
        return res;
    }
    int query(int l, int r)
    {
        return query(r) - query(l);
    }
};

struct LazyBit
{
    RangeBit bitAdd, bitSub;
    void update(int l, int r, int val)
    {
        bitAdd.update(l, r, val);
        bitSub.update(l, (l - 1) * val);
        bitSub.update(r + 1, (-r) * val);
    }
    int query(int idx)
    {
        return idx * bitAdd.query(idx) - bitSub.query(idx);
    }
    int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};