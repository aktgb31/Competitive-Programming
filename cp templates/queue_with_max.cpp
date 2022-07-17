const ll inf = 1e18;
#define x first
#define y second
#define mp make_pair
typedef pair<ll, ll> pll;
struct myQueue
{
    stack<pll> s1, s2;

    int size()
    {
        return s1.size() + s2.size();
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    long long getMax()
    {
        if (isEmpty())
        {
            return -inf;
        }
        if (!s1.empty() && !s2.empty())
        {
            return max(s1.top().y, s2.top().y);
        }
        if (!s1.empty())
        {
            return s1.top().y;
        }
        return s2.top().y;
    }

    void push(long long val)
    {
        if (s2.empty())
        {
            s2.push(mp(val, val));
        }
        else
        {
            s2.push(mp(val, max(val, s2.top().y)));
        }
    }

    void pop()
    {
        if (s1.empty())
        {
            while (!s2.empty())
            {
                if (s1.empty())
                {
                    s1.push(mp(s2.top().x, s2.top().x));
                }
                else
                {
                    s1.push(mp(s2.top().x, max(s2.top().x, s1.top().y)));
                }
                s2.pop();
            }
        }
        assert(!s1.empty());
        s1.pop();
    }
};