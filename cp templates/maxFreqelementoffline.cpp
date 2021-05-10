const int MAXA = 300001;
const int MAXN = 300001;
const int MAXQ = 300001;

int a[MAXN];
typedef tuple<int, int, int, int> Query;
Query query[MAXQ];

inline void moAlgorithm(const int n, const int a[], const int q, tuple<int, int, int, int> query[])
{
    const int blockSize = (int)sqrt((long double)n);

    const auto getLeft = [](const Query &q) { return get<0>(q); };
    const auto getRight = [](const Query &q) { return get<1>(q); };
    const auto getBlockIndex = [=](const Query &q) { return getLeft(q) / blockSize; };

    sort(query, query + q, [=](const Query &a, const Query &b) {
        return getBlockIndex(a) < getBlockIndex(b) ||
               getBlockIndex(a) == getBlockIndex(b) && getRight(a) > getRight(b);
    });

    static int count[MAXA + 1];
    memset(count, 0, sizeof(count));
    static int numberOfValuesWithCount[MAXN + 1];
    memset(numberOfValuesWithCount, 0, sizeof(*numberOfValuesWithCount) * (n + 1));
    int maxCount = 0;

    const auto remove = [&](const int index) {
        --numberOfValuesWithCount[count[a[index]]];
        if (count[a[index]] == maxCount && numberOfValuesWithCount[count[a[index]]] == 0)
        {
            --maxCount;
        }
        --count[a[index]];
        ++numberOfValuesWithCount[count[a[index]]];
    };
    const auto add = [&](const int index) {
        --numberOfValuesWithCount[count[a[index]]];
        if (count[a[index]] == maxCount)
        {
            ++maxCount;
        }
        ++count[a[index]];
        ++numberOfValuesWithCount[count[a[index]]];
    };

    int left = 0, right = -1;

    for (int i = 0; i < q; ++i)
    {
        for (; left < getLeft(query[i]); ++left)
        {
            remove(left);
        }
        for (; left > getLeft(query[i]);)
        {
            add(--left);
        }
        for (; right < getRight(query[i]);)
        {
            add(++right);
        }
        for (; right > getRight(query[i]); --right)
        {
            remove(right);
        }
        get<3>(query[i]) = maxCount;
    }

    sort(query, query + q, [=](const Query &a, const Query &b) {
        return get<2>(a) < get<2>(b);
    });
}
