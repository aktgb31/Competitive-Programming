#include <bits/stdc++.h>
using namespace std;

#define db(...)                              \
    cerr << "__debug__ " << __LINE__ << " "; \
    ZZ(#__VA_ARGS__, __VA_ARGS__);

template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename A>
ostream &operator<<(ostream &out, const vector<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A>
ostream &operator<<(ostream &out, const set<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A>
ostream &operator<<(ostream &out, const deque<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}

template <typename A>
ostream &operator<<(ostream &out, const multiset<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A, typename B>
ostream &operator<<(ostream &out, const map<A, B> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A, typename B>
ostream &operator<<(ostream &out, const multimap<A, B> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}

template <typename A>
ostream &operator<<(ostream &out, const unordered_set<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A>
ostream &operator<<(ostream &out, const unordered_multiset<A> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A, typename B>
ostream &operator<<(ostream &out, const unordered_map<A, B> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}
template <typename A, typename B>
ostream &operator<<(ostream &out, const unordered_multimap<A, B> &v)
{
    out << "{ ";
    for (const auto &x : v)
        out << x << ' ';
    out << " } ";
    return out;
}

template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&...args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1 << ", ";
    ZZ(comma, args...);
}

template <typename T>
void deb(T arr[], int n)
{
    cerr << "{ ";
    for (int i = 0; i < n; i++)
        cerr << arr[i] << " ";
    cerr << "} \n";
}
