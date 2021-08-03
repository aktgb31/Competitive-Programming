
//Lazy Segment Tree using Classes

class Node
{
    Node lazylazyMerge(const Node &rhs) //Merges two lazy nodes
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r) //Merges lazy node to segment tree
    {
        Node a = *this;
        a.val += (r - l + 1) * (rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs) //Merges Two segment tree nodes
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    template <typename segNode>
    friend class Segtree;

public:
    long long val;
    Node(long long one = 0) : val(one) {}
};

template <typename segNode>
class Segtree
{
    vector<segNode> Seg, Lazy;
    vector<bool> isLazy;
    int n;
    int outOfRangeValue;

    void propagate(int node, int L, int R)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node] = Seg[node].seglazyMerge(Lazy[node], L, R);
            if (L != R)
            {
                Lazy[2 * node] = Lazy[2 * node].lazylazyMerge(Lazy[node]);
                Lazy[2 * node + 1] = Lazy[2 * node + 1].lazylazyMerge(Lazy[node]);
                isLazy[2 * node] = true;
                isLazy[2 * node + 1] = true;
            }
            Lazy[node] = segNode();
        }
    }

    void build(int node, int start, int end, vector<segNode> &Base) //Recursively Builds the tree
    {
        if (start == end)
        {
            Seg[node] = Base[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, Base);
        build(2 * node + 1, mid + 1, end, Base);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    segNode rQuery(int node, int start, int end, int qstart, int qend) //Range Query
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return segNode(outOfRangeValue);
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) / 2;
        segNode l = rQuery(2 * node, start, mid, qstart, qend);
        segNode r = rQuery(2 * node + 1, mid + 1, end, qstart, qend);
        return l.segSegMerge(r);
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
        int mid = (start + end) / 2;
        rUpdate(2 * node, start, mid, qstart, qend, val);
        rUpdate(2 * node + 1, mid + 1, end, qstart, qend, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }

public:
    Segtree(int _n = 2e5)
    {
        this->n = _n;
        outOfRangeValue = 0;
        cerr << "Change Out of Range Value and also erase this statement";
        Seg.resize(4 * _n + 10);
        Lazy.resize(4 * _n + 10);
        isLazy.resize(4 * _n + 10);
    }

    void build(vector<segNode> &Base)
    {
        n = Base.size();
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
        build(1, 0, n - 1, Base);
    }

    segNode query(int pos)
    {
        return rQuery(1, 0, n - 1, pos, pos);
    }
    segNode query(int left, int right)
    {
        return rQuery(1, 0, n - 1, left, right);
    }
    void update(int pos, segNode val)
    {
        rUpdate(1, 0, n - 1, pos, pos, val);
    }
    void update(int start, int end, segNode val)
    {
        rUpdate(1, 0, n - 1, start, end, val);
    }
};

/*Structures Segment trees

struct Node
{
    long long val;
    Node(long long one = 0) : val(one) {}
    Node lazylazyMerge(const Node &rhs) //Merges two lazy nodes
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r) //Merges lazy node to segment tree
    {
        Node a = *this;
        a.val += (r - l + 1) * (rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs) //Merges Two segment tree nodes
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
};

template <typename segNode>
struct Segtree
{
    vector<segNode> Seg, Lazy;
    vector<bool> isLazy;
    int n;

    void propagate(int node, int L, int R)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node] = Seg[node].seglazyMerge(Lazy[node], L, R);
            if (L != R)
            {
                Lazy[2 * node] = Lazy[2 * node].lazylazyMerge(Lazy[node]);
                Lazy[2 * node + 1] = Lazy[2 * node + 1].lazylazyMerge(Lazy[node]);
                isLazy[2 * node] = true;
                isLazy[2 * node + 1] = true;
            }
            Lazy[node] = segNode();
        }
    }

    void build(int node, int start, int end, vector<Node> &Base) //Recursively Builds the tree
    {
        if (start == end)
        {
            Seg[node] = Base[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, Base);
        build(2 * node + 1, mid + 1, end, Base);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    segNode rQuery(int node, int start, int end, int qstart, int qend) //Range Query
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return segNode();
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) / 2;
        segNode l = rQuery(2 * node, start, mid, qstart, qend);
        segNode r = rQuery(2 * node + 1, mid + 1, end, qstart, qend);
        return l.segSegMerge(r);
    }
    segNode pQuery(int node, int start, int end, int pos) //Point Query
    {
        propagate(node, start, end);
        if (start == end)
            return Seg[node];
        int mid = (start + end) / 2;
        if (pos <= mid)
            return pQuery(2 * node, start, mid, pos);
        return pQuery(2 * node + 1, mid + 1, end, pos);
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
        int mid = (start + end) / 2;
        rUpdate(2 * node, start, mid, qstart, qend, val);
        rUpdate(2 * node + 1, mid + 1, end, qstart, qend, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    void pUpdate(int node, int start, int end, int pos, segNode val)
    {
        propagate(node, start, end);
        if (start == end)
        {
            isLazy[node] = true;
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pUpdate(2 * node, start, mid, pos, val);
        else
            pUpdate(2 * node + 1, mid + 1, end, pos, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }

    ///Public part
    Segtree(int _n = 2e5)
    {
        this->n = _n;
        Seg.resize(4 * _n + 10);
        Lazy.resize(4 * _n + 10);
        isLazy.resize(4 * _n + 10);
    }

    void build(vector<segNode> &Base)
    {
        n = Base.size();
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
        build(1, 0, n - 1, Base);
    }

    segNode query(int pos)
    {
        return pQuery(1, 0, n - 1, pos);
    }
    segNode query(int left, int right)
    {
        return rQuery(1, 0, n - 1, left, right);
    }
    void update(int pos, segNode val)
    {
        pUpdate(1, 0, n - 1, pos, val);
    }
    void update(int start, int end, segNode val)
    {
        rUpdate(1, 0, n - 1, start, end, val);
    }
};
*/
