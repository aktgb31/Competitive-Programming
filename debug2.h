#include <bits/stdc++.h>
using namespace std;

#define db(...)                              \
    cerr << "__debug__ " << __LINE__ << " "; \
    debug::ZZ(#__VA_ARGS__, __VA_ARGS__);

namespace debug
{
    const int colors[] = {31, 32, 33, 34, 35, 36, 39};
    enum code
    {
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        DEFAULT
    };

    int containerCount = 0;

#define color(code) cerr << "\033[" << colors[code] << "m"
#define reset() cerr << "\033[" << colors[DEFAULT] << "m"

    template <typename Ostream, typename X, typename Y>
    inline typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &out, pair<X, Y> const &p)
    {
        color(CYAN);
        out << '[' << p.first;
        color(CYAN);
        out << ", ";
        color(CYAN);
        out << p.second;
        color(CYAN);
        out << ']';
        reset();
        return out;
    }
    template <typename Ostream, typename Cont>
    inline typename enable_if<is_same<Ostream, ostream>::value, Ostream &>::type operator<<(Ostream &out, const Cont &x)
    {
        containerCount %= 5;
        int curr = (RED + containerCount);
        color(curr);
        out << "{";
        for (auto &y : x)
        {
            out << " " << y;
            color(curr);
        }
        out << " }";
        reset();
        ++containerCount;
        return out;
    }

    template <typename Arg1>
    void ZZ(const char *name, Arg1 &&arg1)
    {
        containerCount %= 5;
        color(RED + containerCount);
        while (*name == ',' || *name == ' ')
            name++;
        std::cerr << name << " = " << arg1 << "\n";
        reset();
        ++containerCount;
    }
    template <typename Arg1, typename... Args>
    void ZZ(const char *names, Arg1 &&arg1, Args &&...args)
    {
        containerCount %= 5;
        while (*names == ',' || *names == ' ')
            names++;
        const char *comma = strchr(names + 1, ',');
        color(RED + containerCount);
        std::cerr.write(names, comma - names) << " = " << arg1 << ", ";
        ++containerCount;
        ZZ(comma, args...);
        reset();
    }
}