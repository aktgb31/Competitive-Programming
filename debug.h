#include <bits/stdc++.h>
using namespace std;

#define db(...)                              \
    cerr << "__debug__ " << __LINE__ << " "; \
    debug::ZZ(#__VA_ARGS__, __VA_ARGS__);

namespace debug
{
    template <typename T, typename U>
    ostream &operator<<(ostream &out, const pair<T, U> &p)
    {
        out << '[' << p.first << ", " << p.second << ']';
        return out;
    }
    template <class Ch, class Tr, class Container>
    basic_ostream<Ch, Tr> &operator<<(basic_ostream<Ch, Tr> &out, Container const &x)
    {
        out << "{";
        for (auto &y : x)
            out << " " << y;
        out << " }";
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
}