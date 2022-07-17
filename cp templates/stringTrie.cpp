#include <bits/stdc++.h>

using namespace std;

class stringTrie
{
    bool isEnd;
    stringTrie *child[26];

public:
    stringTrie()
    {
        isEnd = false;
        fill(child, child + 26, nullptr);
    }
    void insert(const string &key)
    {
        stringTrie *p = this;
        for (int i = 0; i < key.length(); i++)
        {
            int idx = key[i] - 'a';
            if (p->child[idx] == nullptr)
                p->child[idx] = new stringTrie();
            p = p->child[idx];
        }
        p->isEnd = true;
    }
};