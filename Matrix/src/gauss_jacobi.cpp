#include "gauss_jacobi.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;

GaussJacobi::GaussJacobi(const Matrix &m, int maxIter, double tol)
    : IterativeMethod(m, maxIter, tol) {}

void GaussJacobi::solve(ofstream &fout)
{
    int n = rows;

    if (cols != n + 1)
        throw runtime_error("Invalid augmented matrix");

    // ✅ Step 1: Create A and b from augmented matrix
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            A[i][j] = mat[i][j];

        b[i] = mat[i][n];   // last column
    }

    // ✅ Step 2: Create Matrix object for A
    Matrix matA(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matA.set(i, j, A[i][j]);

    // ✅ Step 3: Check & convert using Matrix functions
    if (!matA.isDiagonallyDominant())
    {
        fout << "Matrix is not diagonally dominant. Converting...\n";

        Matrix D = matA.makeDiagonallyDominant();

        // 🔥 Reorder A and b accordingly
        vector<vector<double>> newA(n, vector<double>(n));
        vector<double> newB(n);
        vector<bool> used(n, false);

        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < n; k++)
            {
                if (!used[k])
                {
                    bool same = true;

                    for (int j = 0; j < n; j++)
                    {
                        if (fabs(D.get(i, j) - matA.get(k, j)) > 1e-9)
                        {
                            same = false;
                            break;
                        }
                    }

                    if (same)
                    {
                        newA[i] = A[k];
                        newB[i] = b[k];
                        used[k] = true;
                        break;
                    }
                }
            }
        }

        A = newA;
        b = newB;
    }

    // ✅ Step 4: Gauss-Jacobi iteration
    vector<double> x(n, 0.0), x_new(n, 0.0);

    for (int iter = 0; iter < maxIterations; iter++)
    {
        for (int i = 0; i < n; i++)
        {
            if (fabs(A[i][i]) < 1e-12)
                throw runtime_error("Zero diagonal element!");

            double sum = b[i];

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum -= A[i][j] * x[j];
            }

            x_new[i] = sum / A[i][i];
        }

        // ✅ Convergence check
        double error = 0;
        for (int i = 0; i < n; i++)
            error = max(error, fabs(x_new[i] - x[i]));

        if (error < tolerance)
        {
            fout << "Converged in " << iter + 1 << " iterations\n";
            break;
        }

        x = x_new;
    }

    // ✅ Output
    printSolution(fout, x_new);
}