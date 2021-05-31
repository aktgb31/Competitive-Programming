class intTrie
{
    int key;
    intTrie *child[2];

    intTrie *remove(intTrie *root, const int &key, int d = 31)
    {
        if (root == nullptr)
            return nullptr;
        if (d == -1)
        {
            delete (root);
            root = nullptr;
            return root;
        }
        int bit = 1 & (key >> d);
        root->child[bit] = remove(root->child[bit], key, d - 1);
        if (root->child[0] == nullptr && root->child[1] == nullptr)
        {
            delete (root);
            root = nullptr;
        }
        return root;
    }

public:
    intTrie()
    {
        key = 0;
        child[0] = child[1] = nullptr;
    }
    void insert(const int &key)
    {
        intTrie *p = this;
        for (int i = 31; i >= 0; i--)
        {
            int bit = 1 & (key >> i);
            if (p->child[bit] == nullptr)
                p->child[bit] = new intTrie();
            p = p->child[bit];
        }
        p->key = key;
    }
    void remove(const int &key)
    {
        *this = *(remove(this, key));
    }
    void print()
    {
        if (this->child[0] == nullptr && this->child[1] == nullptr)
            cout << this->key << " ";
        if (this->child[0] != nullptr)
            this->child[0]->print();
        if (this->child[1] != nullptr)
            this->child[1]->print();
    }
};
