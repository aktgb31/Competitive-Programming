#include <bits/stdc++.h>

using namespace std;

set<int> points;

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
    void multiplePatternMatching(const string &text)
    {
        for (int i = 0; i < text.size(); i++)
        {
            stringTrie *p = this;
            for (int j = i; j < text.size(); j++)
            {
                if (p->isEnd)
                    points.insert(i);
                int idx = text[j] - 'A';
                if (p->child[idx] == nullptr)
                    break;
                p = p->child[idx];
            }
            if (p->isEnd)
                points.insert(i);
        }
    }
};

int main()
{
    string text;
    cin >> text;
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
    root->multiplePatternMatching(text);
    for (auto &it : points)
        cout << it << " ";
    cout << "\n";
}