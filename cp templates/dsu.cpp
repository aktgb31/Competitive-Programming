
class UnionFind
{
private:
    vector<int> p, setSize; // remember: vi is vector<int>
    int numSets;

public:
    UnionFind(int N)
    {
        setSize.assign(N, 1);
        numSets = N;
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int unionSet(int i, int j)
    {
        i = findSet(i);
        j = findSet(j);
        if (i != j)
        {
            numSets--;
            if (setSize[i] > setSize[j])
                swap(i, j);
            p[i] = j;
            setSize[j] += setSize[i];
            return j;
        }
        return -1;
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};