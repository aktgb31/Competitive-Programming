istream &operator>>(istream &is, __int128 &num)
{
    string s;
    is >> s;
    int i = 0;
    num = 0;
    int neg = 0;
    if (s[i] == '-')
        neg = 1, ++i;
    for (; i < s.size(); i++)
        num = num * 10 + s[i] - '0';
    if (neg)
        num *= -1;
    return is;
}

ostream &operator<<(ostream &os, __int128 num)
{
    if (num < 0)
    {
        os << "-";
        num *= -1;
    }

    string s;
    s.reserve(50);
    for (; num > 0; num /= 10)
        s += num % 10 + '0';

    for (int i = s.size() - 1; i >= 0; i--)
        os << s[i];

    return os;
}