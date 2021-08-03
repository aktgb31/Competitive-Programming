template <typename T = long long int>
class matrix
{
    vector<vector<T>> mat;
    int r, c;

public:
    matrix()
    {
        this->r = 0;
        this->c = 0;
    }
    matrix(int r, int c)
    {
        this->r = r;
        this->c = c;
        mat.assign(r, vector<T>(c));
    }

    matrix(int r, int c, const T &val)
    {
        this->r = r;
        this->c = c;
        mat.assign(r, vector<T>(c, val));
    }

    matrix(int n)
    {
        this->r = this->c = n;
        mat.assign(n, vector<T>(n));
        for (int i = 0; i < n; i++)
            mat[i][i] = (T)1;
    }

    matrix(vector<vector<T>> lst) : mat(lst), r(lst.size()), c(lst[0].size())
    {
        for (int i = 0; i < r; i++)
            assert(this->mat[i].size() == c);
    }

    T sum()
    {
        T res = 0;
        for (const auto &rows : mat)
            for (const auto &cells : rows)
            {
                res = (res + cells);
#ifdef MOD
                res %= MOD;
#endif
            }
        return res;
    }

    matrix operator+(const matrix &B)
    {
        assert(this->r == B.r && this->c == B.c);
        matrix<T> X(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
            {
                X[i][j] = (mat[i][j] + B[i][j]);
#ifdef MOD
                X[i][j] %= MOD;
#endif
            }
        return X;
    }

    matrix operator-()
    {
        matrix<T> C(r, c, 0);
        int i, j;
        for (i = 0; i < r; i++)
            for (j = 0; j < c; j++)
            {
                C[i][j] = -mat[i][j];
#ifdef MOD
                C[i][j] %= MOD;
                if (C[i][j] < 0)
                    C[i][j] += MOD;
#endif
            }

        return C;
    }

    matrix operator*(const matrix &B)
    {
        assert(this->c == B.r);
        matrix<T> X(r, B.c, 0);

        for (int j = 0; j < B.c; ++j)
            for (int k = 0; k < c; ++k)
            {
                T temp = B[k][j];
                for (int i = 0; i < r; ++i)
                {
                    X[i][j] = X[i][j] + (mat[i][k] * temp);
#ifdef MOD
                    X[i][j] %= MOD;
#endif
                }
            }

        return X;
    }
    static matrix power(matrix A, long long y)
    {
        assert(A.r == A.c);
        matrix<T> res(A.r);
        while (y > 0)
        {
            if (y & 1)
                res = (res * A);
            y = y >> 1;
            A = A * A;
        }
        return res;
    }

    vector<T> &operator[](int i)
    {
        return mat.at(i);
    }
    const vector<T> &operator[](int i) const
    {
        return mat.at(i);
    }

    friend istream &operator>>(istream &in, matrix &M)
    {
        for (int i = 0; i < M.r; i++)
            for (int j = 0; j < M.c; j++)
                in >> M[i][j];

        return in;
    }
    friend ostream &operator<<(ostream &out, const matrix &M)
    {
        for (int i = 0; i < M.r; i++)
        {
            for (int j = 0; j < M.c; j++)
                out << M[i][j] << " ";
            out << "\n";
        }
        return out;
    }
};