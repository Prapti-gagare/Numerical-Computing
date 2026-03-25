#include "gauss_seidle.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;

GaussSeidel::GaussSeidel(const Matrix &m, int maxIter, double tol)
    : IterativeMethod(m, maxIter, tol) {}

void GaussSeidel::solve(ofstream &fout)
{
    int n = rows;

    if (cols != n + 1)
        throw runtime_error("Invalid augmented matrix");

    // ✅ Step 1: Create square matrix A
    Matrix A(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A.set(i, j, mat[i][j]);

    // ✅ Step 2: Check & convert using your Matrix functions
    Matrix D = A;

    if (!A.isDiagonallyDominant())
    {
        fout << "Matrix is not diagonally dominant. Converting...\n";

        D = A.makeDiagonallyDominant();
    }

    // ✅ Step 3: Reorder augmented matrix according to D
    vector<vector<double>> newMat(n, vector<double>(cols));
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
                    if (fabs(D.get(i, j) - A.get(k, j)) > 1e-9)
                    {
                        same = false;
                        break;
                    }
                }

                if (same)
                {
                    newMat[i] = mat[k];   // copy full row (A + b)
                    used[k] = true;
                    break;
                }
            }
        }
    }

    mat = newMat;   // update augmented matrix

    // ✅ Step 4: Gauss-Seidel iteration
    vector<double> x(n, 0.0);

    for (int iter = 0; iter < maxIterations; iter++)
    {
        double error = 0;

        for (int i = 0; i < n; i++)
        {
            if (fabs(mat[i][i]) < 1e-12)
                throw runtime_error("Zero diagonal element!");

            double sum = mat[i][n]; // RHS

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum -= mat[i][j] * x[j];
            }

            double x_old = x[i];
            x[i] = sum / mat[i][i];

            error = max(error, fabs(x[i] - x_old));
        }

        if (error < tolerance)
        {
            fout << "Converged in " << iter + 1 << " iterations\n";
            break;
        }
    }

    printSolution(fout, x);
}