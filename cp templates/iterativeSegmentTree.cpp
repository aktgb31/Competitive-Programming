#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    constexpr static int IDENTITY() { return 0; } // Change indentity here. Indentity is static casted
    int value;
    node(int x = IDENTITY()) : value(x){};
    static node merge(const node &a, const node &b)
    {
        node res;
        res.value = a.value + b.value; // Change here
        return res;
    }
    template <typename T>
    operator T() const { return static_cast<T>(value); };
    template <typename Ostream>
    friend typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const node &t);
};
template <typename Ostream>
typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const node &t)
{
    os << t.value;
    return os;
}

template <class segNode>
class segTree
{
private:
    int size;
    std::vector<segNode> d;
    void update(int k) { d[k] = segNode::merge(d[k << 1], d[k << 1 | 1]); }

public:
    segTree() : segTree(0) {}
    explicit segTree(int n) : segTree(std::vector<segNode>(n, static_cast<segNode>(segNode::IDENTITY()))) {}
    explicit segTree(const std::vector<segNode> &v) : size(int(v.size()))
    {
        d = std::vector<segNode>(2 * size, static_cast<segNode>(segNode::IDENTITY()));
        for (int i = 0; i < size; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--)
            update(i);
    }
    void set(int p, segNode x)
    {
        assert(0 <= p && p < size);
        for (d[p += size] = x; p > 1; p >>= 1)
            update(p >> 1);
    }
    segNode get(int p) const
    {
        assert(0 <= p && p < size);
        return d[p + size];
    }
    segNode get(int l, int r) const // l inclusive r exclusive here
    {
        assert(0 <= l && l <= r && r <= size);
        segNode sml = static_cast<segNode>(segNode::IDENTITY()), smr = static_cast<segNode>(segNode::IDENTITY());
        l += size;
        r += size;
        while (l < r)
        {
            if (l & 1)
                sml = segNode::merge(sml, d[l++]);
            if (r & 1)
                smr = segNode::merge(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return segNode::merge(sml, smr);
    }
    segNode getAll() const { return d[1]; }

    template <bool (*fun)(segNode)>
    int max_right(int l) const //max right such that fun(l to r-1) is true
    {
        return max_right(l, [](segNode x)
                         { return fun(x); });
    }

    template <class F>
    int max_right(int l, F fun) const //max right such that fun(l to r-1) is true
    {
        assert(0 <= l && l <= size);
        assert(fun(static_cast<node>(segNode::IDENTITY())));
        if (l == size)
            return size;
        l += size;
        segNode sm = static_cast<node>(segNode::IDENTITY());
        do
        {
            while ((l & 1) == 0)
                l >>= 1;
            if (!fun(segNode::merge(sm, d[l])))
            {
                while (l < size)
                {
                    l = (l << 1);
                    if (fun(segNode::merge(sm, d[l])))
                    {
                        sm = segNode::merge(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = segNode::merge(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return size;
    }

    template <bool (*fun)(segNode)>
    int min_left(int r) const //min left such that fun(l to r-1) is true
    {
        return min_left(r, [](segNode x)
                        { return fun(x); });
    }
    template <class F>
    int min_left(int r, F fun) const ////min left such that fun(l to r-1) is true
    {
        assert(0 <= r && r <= size);
        assert(fun(static_cast<node>(segNode::IDENTITY())));
        if (r == 0)
            return 0;
        r += size;
        segNode sm = static_cast<node>(segNode::IDENTITY());
        do
        {
            r--;
            while (r > 1 && (r & 1))
                r >>= 1;
            if (!fun(segNode::merge(d[r], sm)))
            {
                while (r < size)
                {
                    r = (r << 1 | 1);
                    if (fun(segNode::merge(d[r], sm)))
                    {
                        sm = segNode::merge(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = segNode::merge(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
    template <typename Ostream, typename T>
    friend typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const segTree<T> &t);
};

template <typename Ostream, typename T>
typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &os, const segTree<T> &t)
{
    for (int i = 0; i < t.size; i++)
        os << t.get(i) << " ";
    return os;
}
