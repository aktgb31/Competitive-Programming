#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define db(...)
#endif
using namespace std;

// When size is known
struct Vertex
{
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0)
    {
        if (l)
            sum += l->sum;
        if (r)
            sum += r->sum;
    }
};

Vertex *build(const vector<int> &a, int tl, int tr)
{
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm + 1, tr));
}

int get_sum(Vertex *v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm)) + get_sum(v->r, tm + 1, tr, max(l, tm + 1), r);
}

Vertex *update(Vertex *v, int tl, int tr, int pos, int new_val)
{
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm + 1, tr, pos, new_val));
}
////

//implicit segment trees
struct Vertex
{
    int left, right;
    int sum = 0;
    Vertex *left_child = nullptr, *right_child = nullptr;

    Vertex(int lb, int rb)
    {
        left = lb;
        right = rb;
    }

    void extend()
    {
        if (!left_child && left + 1 < right)
        {
            int t = (left + right) / 2;
            left_child = new Vertex(left, t);
            right_child = new Vertex(t, right);
        }
    }

    void add(int k, int x)
    {
        extend();
        sum += x;
        if (left_child)
        {
            if (k < left_child->right)
                left_child->add(k, x);
            else
                right_child->add(k, x);
        }
    }

    int get_sum(int lq, int rq)
    {
        if (lq <= left && right <= rq)
            return sum;
        if (max(left, lq) >= min(right, rq))
            return 0;
        extend();
        return left_child->get_sum(lq, rq) + right_child->get_sum(lq, rq);
    }
};

//Demoraliser
const int N = 1e5 + 5;

struct node
{
    node *left, *right;
    int val = 0;
    void merge(node *l, node *r)
    {
        val = l->val + r->val;
    }
};

node ns[35 * N];
int cnt = 0;

node *create()
{
    node *tmp;
    if (cnt < 35 * N)
        tmp = &ns[cnt++];
    else
        tmp = new node();
    tmp->val = 0;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}
struct dynamicsegtree
{
    node *root;
    dynamicsegtree()
    {
        root = create();
    }

    node *update(node *x, int tl, int tr, int pos, int val)
    {
        node *ret = create();
        ret->left = x->left;
        ret->right = x->right;
        if (tl == tr)
        {
            ret->val = val;
            return ret;
        }
        int tm = tl + (tr - tl) / 2;

        if (!ret->left)
            ret->left = create();
        if (!ret->right)
            ret->right = create();
        if (tm >= pos)
        {
            ret->left = update(ret->left, tl, tm, pos, val);
        }
        else
        {
            ret->right = update(ret->right, tm + 1, tr, pos, val);
        }

        ret->merge(ret->left, ret->right);
        return ret;
    }
    node *upd(node *x, int pos, int val)
    {
        return update(x, 0, N - 1, pos, val);
    }

    int descent(node *x, int tl, int tr, int k, int &prev)
    {
        int here = 0;
        if (x)
            here = x->val;
        if (prev + here < k)
        {
            prev += here;
            return N;
        }
        if (tl == tr)
            return tl;

        int tm = tl + (tr - tl) / 2;

        int ans = descent(x->left, tl, tm, k, prev);
        if (ans != N)
            return ans;
        return descent(x->right, tm + 1, tr, k, prev);
    }

    int descent(node *x, int k)
    {
        int prev = 0;
        return descent(x, 0, N - 1, k, prev);
    }
}