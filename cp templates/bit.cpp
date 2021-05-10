#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Bit
{
    int size;
    vector<T> bit;
    Bit(int size)
    {
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