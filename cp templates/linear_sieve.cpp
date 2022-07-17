const int N = 1000000;
int lp[N + 1];
int prime[100000];

void sieve()
{
    int idx = 0;
    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            prime[idx++] = i;
        }
        int product = i * prime[0];
        for (int j = 0; j < idx && prime[j] <= lp[i] && product <= N; ++j, product = i * prime[j])
            lp[product] = prime[j];
    }
};