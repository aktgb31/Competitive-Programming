
int A[MAX];
int tree[4 * MAX];
int lazy[4 * MAX];
int combine(int l, int r)
{
    return l + r;
}
void build(int node, int start, int end)
{
    if (start == end)
        tree[node] = A[start];
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}
void update(int node, int start, int end, int idx)
{
    if (start == end)
    {
        tree[node] = A[start];
    }
    else
    {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update(2 * node, start, mid, idx);
        else
            update(2 * node + 1, mid + 1, end, idx);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}
int query(int node, int start, int end, int l, int r)
{
    if (r < start || l > end)
        return 0;
    if (l <= start && r >= end)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return combine(p1, p2);
}
void updaterange(int node, int start, int end, int l, int r, int val)
{
    if (lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > r || end < l)
        return;
    if (l <= start && r >= end)
    {
        tree[node] += (end - start + 1) * val;
        if (start != end)
        {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    ll mid = (start + end) / 2;
    updaterange(2 * node, start, mid, l, r, val);
    updaterange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}
ll queryrange(int node, int start, int end, int l, int r)
{
    if (start > end || start > r || end < l)
    {
        return 0;
    }
    if (lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (l <= start && r >= end)
        return tree[node];
    int mid = (start + end) / 2;
    ll p1 = queryrange(2 * node, start, mid, l, r, val);
    ll p2 = queryrange(2 * node + 1, mid + 1, end, l, r, val);
    return combine(p1, p2);
}
