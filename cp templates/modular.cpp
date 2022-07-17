namespace Modular
{
    template <typename T, typename U>
    inline void mod_add(T &a, const U &b)
    {
        a = (a + b) % mod;
    }
    template <typename T, typename U>
    inline void mod_sub(T &a, const U &b)
    {
        a = (a - b + mod) % mod;
    }
    template <typename T, typename U>
    inline void mod_mul(T &a, const U &b)
    {
        a = (1ll * a * b) % mod;
    }
};
using namespace Modular;