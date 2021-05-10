#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;
class Mod
{
    long long val;
    long long power(long long x, long long y)
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

public:
    Mod(long long c = 0) { val = c % mod; };
    friend ostream &operator<<(ostream &out, const Mod &c);
    friend istream &operator>>(istream &in, Mod &c);
    Mod operator+(Mod const &obj)
    {
        Mod temp;
        temp.val = (val + obj.val) % mod;
        return temp;
    }
    void operator+=(Mod const &obj)
    {
        val = (val + obj.val) % mod;
    }
    Mod operator-(Mod const &obj)
    {
        Mod temp;
        temp.val = (val - obj.val + mod) % mod;
        return temp;
    }
    void operator-=(Mod const &obj)
    {
        val = (val - obj.val + mod) % mod;
    }
    Mod operator*(Mod const &obj)
    {
        Mod temp;
        temp.val = (val * obj.val) % mod;
        return temp;
    }
    void operator*=(Mod const &obj)
    {
        val = (val * obj.val) % mod;
    }
    Mod operator/(Mod const &obj)
    {
        if (__gcd(val, obj.val) != 1)
        {
            cerr << "Gcd!=1";
            exit(1);
        }
        Mod temp;
        temp.val = (val * power(obj.val, mod - 2)) % mod;
        return temp;
    }
    void operator/=(Mod const &obj)
    {
        if (__gcd(val, obj.val) != 1)
        {
            cerr << "Gcd!=1";
            exit(1);
        }
        val = (val * power(obj.val, mod - 2)) % mod;
    }
};

ostream &operator<<(ostream &out, const Mod &c)
{
    out << c.val;
    return out;
}
istream &operator>>(istream &in, Mod &c)
{
    in >> c.val;
    return in;
}