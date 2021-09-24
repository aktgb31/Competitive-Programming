
//For God and country
//This problem is a variation of the travelling salesman problem
#include <bits/stdc++.h>
#include "debug.h"
using namespace std;
#define all(x) x.begin(), x.end()
int VISITED_ALL, n;
vector<vector<int>> graph, path, dp;

int make_ADM(string a, string b)
{
    for (int i = 0; i < a.length(); i++)
    {
        //https://www.geeksforgeeks.org/stdstringrfind-in-c-with-examples/
        //This checks how many characters are common at the end of A and at
        //start of B
        if (b.rfind(a.substr(i), 0) == 0)
            return (b.length() - (a.length() - i));
    }
    return b.length();
}

int tsp(int bitmask, int pos)
{
    //Base condition
    if (bitmask == VISITED_ALL)
        return 0;
    //Check if previously calculated
    if (dp[bitmask][pos] != -1)
        return dp[bitmask][pos];
    int ans = INT_MAX, next;
    //ans stores the minimum cost with pos source
    //best stores the next stop
    //Now we look for unvisited cities
    for (int city = 0; city < n; city++)
    {
        //This will check if this city is unvisited
        if ((bitmask & (1 << city)) == 0)
        {
            int dist = graph[pos][city] + tsp(bitmask | (1 << city), city);
            //We recur with updated path and different source (subtree)
            if (ans > dist)
            {
                ans = dist;
                next = city;
            }
        }
    }
    path[bitmask][pos] = next;
    return dp[bitmask][pos] = ans;
}

string make_path(vector<string> &A, int k)
{
    //The current node
    int cur = k;
    //The resultant string will always start with the source string
    string res = A[k];
    //We denote the path using the bitmask
    int bitmask = (1 << k);
    //Store the next node
    int next = path[bitmask][k];
    while (next != -1)
    {
        //Add the part of the next string needed
        res += A[next].substr(A[next].length() - graph[cur][next]);
        //Update everything
        //The bitmask
        bitmask = bitmask | (1 << next);
        //The cur node
        cur = next;
        //The next node
        next = path[bitmask][next];
    }
    return res;
}

string shortestSuperstring(vector<string> &A)
{
    n = A.size();
    VISITED_ALL = (1 << n) - 1;
    //We will make an 'adjacency matrix'
    //Suppose there is a string A and string B, this graph stores how many
    //character we need to add to A inorder to make B a substring of the
    //combined string ex A = 'catg' and B = 'gcta'. Combined string is
    //'catgcta'. Therefore graph[][] = 3
    graph.assign(n, vector<int>(n, 0));
    //https://www.geeksforgeeks.org/vector-assign-in-c-stl/
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = make_ADM(A[i], A[j]);
    //We need to use bitmask DP here
    string ans;
    //This stores the resultant string
    int ansLen = INT_MAX;
    //This stores the length of the resultant string
    //Both of these need to minimum
    //Now we will take each node as starting and find the smallest hamiltoninan path
    //for it and then we output the smallest amongst them.
    for (int k = 0; k < n; k++)
    {
        //We reset the path and dp matrix for every starting point
        //Rows = 1<<n and Cols = n
        //dp stores the cost for a particular path at a particular position
        //path stores the next visited node for a particular path and position
        dp.assign((1 << n), vector<int>(n, -1));
        path.assign((1 << n), vector<int>(n, -1));
        //Travelling Salesman Problem DP
        int z = tsp((1 << k), k);
        //Now we have to construct the shortest string with the kth string as start
        string res = make_path(A, k);
        //Store the shortest result
        if (res.length() < ansLen)
        {
            ans = res;
            ansLen = res.length();
        }
    }
    return ans;
}

void process(vector<string> &A)
{
    sort(all(A), [&](const string &a, const string &b)
         { return a.size() > b.size(); });

    vector<int> skip(A.size());
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (A[i].find(A[j]) != string::npos)
                skip[j] = true;

    vector<string> temp;
    for (int i = 0; i < A.size(); i++)
        if (!skip[i])
            temp.push_back(A[i]);
    A = temp;
}
int solve(vector<string> &A)
{
    process(A);
    return shortestSuperstring(A).length();
}
int main()
{
    vector<string> a = {"abcd", "bc", "efgh", "hen", "dog"};
    cout << solve(a);
    // db(a);
    return 0;
}