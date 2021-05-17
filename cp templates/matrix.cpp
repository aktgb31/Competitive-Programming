#include <bits/stdc++.h>
using namespace std;

//Class version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class matrix
{
private:
    vector<vector<long long>> MAT;

public:
    matrix(){};
    matrix(const int &n, const int &m)
    {
        MAT.resize(n, vector<long long>(m));
    }
    matrix(vector<vector<long long>> temp)
    {
        MAT = temp;
    }
    void unit()
    {
        for (int i = 0; i < MAT.size(); ++i)
            MAT[i][i] = 1;
    }

    const vector<long long> &operator[](unsigned i) const
    {
        return MAT[i];
    }
    vector<long long> &operator[](unsigned i)
    {
        return MAT[i];
    }

    matrix operator+(const matrix &B)
    {
        int n = MAT.size(), m = MAT.size();
        matrix X(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                X[i][j] = (MAT[i][j] + B[i][j]);
            }
        return X;
    }
    matrix operator*(const matrix &B)
    {
        int n = MAT.size(), m = MAT[0].size(), o = B[0].size();
        matrix X(n, o);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < o; ++j)
                for (int k = 0; k < m; ++k)
                    X[i][j] = (X[i][j] + (MAT[i][k] * B[k][j]));

        return X;
    }
    static matrix power(matrix A, long long y)
    {
        matrix res(A[0].size(), A[0].size());
        res.unit();
        while (y > 0)
        {
            if (y & 1)
                res = (res * A);
            y = y >> 1;
            A = A * A;
        }
        return res;
    }
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// namespace version
namespace matrixOperations
{
    using T = long long;
#define dim(n, m) (n, vector<T>(m))
    typedef vector<vector<T>> matrix;

    long long matrixSum(const matrix &A)
    {
        long long res = 0;
        for (const auto &rows : A)
            for (const auto &cells : rows)
                res = (res + cells);
        return res;
    }

    inline matrix operator+(const matrix &A, const matrix &B)
    {
        int n = A.size(), m = A[0].size();
        matrix X dim(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                X[i][j] = (A[i][j] + B[i][j]);
            }
        return X;
    }
    void unit(matrix &MAT)
    {
        for (int i = 0; i < MAT.size(); ++i)
            MAT[i][i] = 1;
    }

    inline matrix operator*(const matrix &A, const matrix &B)
    {
        int n = A.size(), m = A[0].size(), o = B[0].size();
        matrix X dim(n, o);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < o; ++j)
                for (int k = 0; k < m; ++k)
                    X[i][j] = (X[i][j] + (A[i][k] * B[k][j]));

        return X;
    }
    inline matrix power(matrix A, long long y)
    {
        matrix res dim(A[0].size(), A[0].size());
        unit(res);
        while (y > 0)
        {
            if (y & 1)
                res = (res * A);
            y = y >> 1;
            A = A * A;
        }
        return res;
    }
};
using namespace matrixOperations;
