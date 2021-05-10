
//Segment Tree using Classes

class Node
{
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
    vector<segNode> Seg;
    int n;

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
        if (start == end)
            return Seg[node];
        int mid = (start + end) / 2;
        if (pos <= mid)
            return pQuery(2 * node, start, mid, pos);
        return pQuery(2 * node + 1, mid + 1, end, pos);
    }

    void pUpdate(int node, int start, int end, int pos, segNode val)
    {
        if (start == end)
        {
            Seg[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pUpdate(2 * node, start, mid, pos, val);
        else
            pUpdate(2 * node + 1, mid + 1, end, pos, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }

public:
    Segtree(int _n = 2e5)
    {
        this->n = _n;
        Seg.resize(4 * _n + 10);
    }

    void build(vector<segNode> &Base)
    {
        n = Base.size();
        Seg.resize(4 * n + 10);
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
};
