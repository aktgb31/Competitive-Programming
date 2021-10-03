#include <bits/stdc++.h>

using namespace std;

template <class T>
class Compress
{
    int n;
    vector<T> val;
    vector<T> &a;

public:
    Compress(vector<T> &arr) : n(arr.size()), a(arr)
    {
        val.reserve(arr.size());
        for (const auto &it : arr)
            val.push_back(it);
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
    }
    void change() // Changes arr to compressed cordinates
    {
        for (int i = 0; i < n; i++)
            a[i] = operator[](i);
    }
    const int operator[](int x) const // Returns compressed value of a[x]
    {
        assert(x >= 0 && x < n);
        return lower_bound(val.begin(), val.end(), a[x]) - val.begin();
    }
    const T &at(int x) const //Returns original value at compressed point x
    {
        assert(x >= 0 && x < val.size());
        return val[x];
    }
};