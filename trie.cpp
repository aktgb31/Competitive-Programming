#include <bits/stdc++.h>

using namespace std;

class stringTrie
{
    bool isEnd;
    int index;
    vector<stringTrie *> child;

public:
    stringTrie()
    {
        index = -1;
        isEnd = false;
        child.resize(26, nullptr);
    }
    void insert(const string &key)
    {
        stringTrie *p = this;
        for (int i = 0; i < key.length(); i++)
        {
            int idx = key[i] - 'A';
            if (p->child[idx] == nullptr)
                p->child[idx] = new stringTrie();
            p = p->child[idx];
        }
        p->isEnd = true;
    }
    friend void label(stringTrie *root, int &index);
};

void label(stringTrie *root, int &index)
{
    root->index = index++;
    for (int i = 0; i < 26; i++)
    {
        if (root->child[i] != nullptr)
        {
            label(root->child[i], index);
            cout << root->index << "->" << root->child[i]->index << ":" << (char)('A' + i) << "\n";
        }
    }
}

int main()
{
    int n;
    cin >> n;
    string s;
    stringTrie *root = new stringTrie();
    while (n--)
    {
        string s;
        cin >> s;
        root->insert(s);
    }
    int index = 0;
    label(root, index);
}