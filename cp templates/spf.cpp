#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int spf[MAXN];
void leastPrimeFactor(int n)
{

    vector<int> least_prime(n + 1, 0);

    least_prime[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (least_prime[i] == 0)
        {
            least_prime[i] = i;
            for (int j = 2 * i; j <= n; j += i)
                if (least_prime[j] == 0)
                    least_prime[j] = i;
        }
    }
}
void sieve()
{
    spf[1] = 1;
    for (int i = 2; i < MAXN; i++)

        spf[i] = i;

    for (int i = 4; i < MAXN; i += 2)
        spf[i] = 2;

    for (int i = 3; i * i < MAXN; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j < MAXN; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

vector<int> getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}