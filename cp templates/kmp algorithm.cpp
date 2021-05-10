void computeLPS(int m, int lps[], char pat[])
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp(string pat, string txt)
{
    int m = pat.size();
    int n = txt.size();
    int lps[m];

    computeLPS(m, lps, pat);
    int i = 0, j = 0;
    while (i < n)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == m)
        {
            cout << "Found at " << i - j;
            j = lps[j - 1];
        }
        else if (i < n && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}