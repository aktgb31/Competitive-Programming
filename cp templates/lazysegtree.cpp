#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;
class Node
{
public:
    long long value;
    Node() { value = 0; }; // Identity
    explicit Node(long long v) { value = v; }
    static Node mergeSegNodes(const Node &a, const Node &b)
    {
        Node res;
        res.value = (a.value + b.value);
        return res;
    }
    void mergeLazyNodes(const Node &b)
    {
        this->value += b.value;
    }
    void mergeSegLazy(const Node &b, const int &l, const int &r)
    {
        this->value += (r - l + 1) * b.value;
    }

    template <typename T>
    explicit operator T() { return static_cast<T>(value); }
    template <typename Ostream>
    friend typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const Node &t);
};
template <typename Ostream>
typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const Node &t)
{
    os << t.value;
    return os;
}

template <typename segNode>
class segTree
{
    int size;
    vector<segNode> Seg;
    vector<segNode> Lazy;
    vector<bool> isLazy;

    void propagate(int node, int l, int r)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node].mergeSegLazy(Lazy[node], l, r);
            if (l != r)
            {
                int mid = (l + r) >> 1;
                Lazy[node + 1].mergeLazyNodes(Lazy[node]);
                Lazy[node + 2 * (mid - l + 1)].mergeLazyNodes(Lazy[node]);
                isLazy[node + 1] = true;
                isLazy[node + 2 * (mid - l + 1)] = true;
            }
            Lazy[node] = segNode();
        }
    }

    void build(int node, int start, int end, const vector<segNode> &Base) //Recursively Builds the tree
    {
        if (start == end)
        {
            Seg[node] = Base[start];
            return;
        }
        int mid = (start + end) >> 1;
        build(node + 1, start, mid, Base);
        build(node + 2 * (mid - start + 1), mid + 1, end, Base);
        Seg[node] = segNode::mergeSegNodes(Seg[node + 1], Seg[node + 2 * (mid - start + 1)]);
    }

    segNode rQuery(int node, int start, int end, int qstart, int qend) //Range Query
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return segNode();
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) >> 1;
        segNode l, r;
        if (qstart <= mid)
            l = rQuery(node + 1, start, mid, qstart, qend);
        if (qend >= mid + 1)
            r = rQuery(node + 2 * (mid - start + 1), mid + 1, end, qstart, qend);
        return segNode::mergeSegNodes(l, r);
    }

    void rUpdate(int node, int start, int end, int qstart, int qend, segNode val)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return;
        if (qstart <= start && end <= qend)
        {
            isLazy[node] = true;
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) >> 1;

        if (qstart <= mid)
            rUpdate(node + 1, start, mid, qstart, qend, val);
        if (qend >= mid + 1)
            rUpdate(node + 2 * (mid - start + 1), mid + 1, end, qstart, qend, val);
        Seg[node] = segNode::mergeSegNodes(Seg[node + 1], Seg[node + 2 * (mid - start + 1)]);
    }

public:
    segTree() : segTree(0){};
    explicit segTree(int n) : size(n), Seg(n << 1), Lazy(n << 1), isLazy(n << 1){};
    explicit segTree(const vector<segNode> &Base) : size(Base.size())
    {
        Seg = vector<segNode>(size << 1);
        Lazy = vector<segNode>(size << 1);
        isLazy = vector<bool>(size << 1);
        build(1, 0, size - 1, Base);
    }
    segNode get(int pos)
    {
        assert(pos >= 0 && pos < size);
        return rQuery(1, 0, size - 1, pos, pos);
    }
    segNode get(int left, int right)
    {
        assert(left <= right && left >= 0 && right < size);
        return rQuery(1, 0, size - 1, left, right);
    }
    void update(int pos, segNode val)
    {
        assert(pos >= 0 && pos < size);
        rUpdate(1, 0, size - 1, pos, pos, val);
    }
    void update(int left, int right, segNode val)
    {
        assert(left <= right && left >= 0 && right < size);
        rUpdate(1, 0, size - 1, left, right, val);
    }
    template <typename Ostream, typename T>
    friend typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, segTree<T> &t);
};

template <typename Ostream, typename T>
typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, segTree<T> &t)
{
    for (int i = 0; i < t.size; i++)
        os << t.get(i) << " ";
    return os;
}
