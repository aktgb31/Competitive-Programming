template <int HASH_LEVEL = 1>
class RabinKarpHash
{
private:
    static inline bool initialised = false;
    static constexpr const int MAXN = 1e5 + 10;
    long long power(long long x, long long y, long long mod)
    {
        long long res = 1;
        x = x % mod;
        while (y > 0)
        {
            if (y & 1)
                res = (res * x) % mod;
            y = y >> 1;
            x = (x * x) % mod;
        }
        return res;
    }

protected:
    static constexpr const int p[3] = {31, 29, 33};
    static constexpr const int m[3] = {1000000007, 1000000009, 998244353};
    static inline int p_pow[HASH_LEVEL][MAXN];
    static inline int inv_pow[HASH_LEVEL][MAXN];

public:
    static_assert(HASH_LEVEL <= 3 && HASH_LEVEL >= 1);
    RabinKarpHash()
    {
        if (!initialised)
        {
            initialised = true;
            for (int j = 0; j < HASH_LEVEL; j++)
            {
                p_pow[j][0] = 1;
                for (int i = 1; i < MAXN; i++)
                    p_pow[j][i] = (1ll * p_pow[j][i - 1] * p[j]) % m[j];
                inv_pow[j][MAXN - 1] = power(p_pow[j][MAXN - 1], m[j] - 2, m[j]);
                for (int i = MAXN - 2; i >= 0; i--)
                    inv_pow[j][i] = (1ll * inv_pow[j][i + 1] * p[j]) % m[j];
            }
        }
    }
    array<int, HASH_LEVEL> getHash(const string &s, const int &start, const int &end)
    {
        array<int, HASH_LEVEL> temp;
        temp.fill(0);
        for (int j = 0; j < HASH_LEVEL; j++)
        {
            for (int i = start; i <= end; i++)
                temp[j] = (temp[j] + (1ll * (s.at(i) - 'a' + 1) * p_pow[j][i]) % m[j]) % m[j];
            temp[j] = (1ll * temp[j] * inv_pow[j][start]) % m[j];
        }
        return temp;
    }
};

template <int HASH_LEVEL = 1>
class StringHash : public RabinKarpHash<HASH_LEVEL>
{
private:
    vector<int> strHash[HASH_LEVEL];
    int len;

protected:
    using RabinKarpHash<HASH_LEVEL>::p_pow;
    using RabinKarpHash<HASH_LEVEL>::inv_pow;
    using RabinKarpHash<HASH_LEVEL>::m;
    using RabinKarpHash<HASH_LEVEL>::p;

public:
    using RabinKarpHash<HASH_LEVEL>::getHash;
    static_assert(HASH_LEVEL <= 3 && HASH_LEVEL >= 1);
    StringHash()
    {
        len = 0;
    }
    StringHash(const string &str)
    {
        len = str.length();
        for (int j = 0; j < HASH_LEVEL; j++)
        {
            strHash[j].resize(len + 1);
            strHash[j][0] = 0;

            for (int i = 0; i < len; i++)
                strHash[j][i + 1] = (strHash[j][i] + (1ll * (str[i] - 'a' + 1) * p_pow[j][i]) % m[j]) % m[j]; // i+1 of strHash mapped to i of pow and inv_pow
        }
    }
    array<int, HASH_LEVEL> getHash(int l, int r)
    {
        assert(r <= len && l <= r && l >= 0);
        array<int, HASH_LEVEL> h;
        h.fill(0);
        for (int j = 0; j < HASH_LEVEL; j++)
        {
            h[j] = (strHash[j][r + 1] - strHash[j][l] + m[j]) % m[j];
            h[j] = (1ll * h[j] * inv_pow[j][l]) % m[j]; // i+1 of strHash mapped to i of pow and inv_pow
        }
        return h;
    }
    void add(const string &str)
    {
        for (int j = 0; j < HASH_LEVEL; j++)
            for (int i = 0; i < str.size(); i++, len++)
                strHash[j][len + 1] = (strHash[j][len] + (1ll * (str[i] - 'a' + 1) * p_pow[j][len]) % m[j]) % m[j];
    }
};
