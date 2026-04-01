#include "cholsky.hpp"
#include <cmath>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "matrix.hpp"

using namespace std;

// Constructor
CholeskyDecomposition::CholeskyDecomposition(const Matrix &m) : LU(m) {}

// Solve function
void CholeskyDecomposition::solve(ofstream &fout)
{
    int n = rows;

    if (rows != cols - 1)
    {
        fout << "Cholesky requires square matrix.\n";
        return;
    }

    // Check symmetry
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] != mat[j][i])
            {
                fout << "Matrix is not symmetric. Cholesky not possible.\n";
                return;
            }

    // Compute L matrix
    vector<vector<double>> L(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j)
            {
                double val = mat[i][i] - sum;
                if (val <= 0)
                {
                    fout << "Matrix not positive definite.\n";
                    return;
                }
                L[i][j] = sqrt(val);
            }
            else
            {
                L[i][j] = (mat[i][j] - sum) / L[j][j];
            }
        }
    }

    // Forward substitution Ly = b
    vector<double> b(n);
    for (int i = 0; i < n; i++)
        b[i] = mat[i][cols - 1];

    vector<double> y = forwardSubstitution(L, b);

    // Backward substitution Ux = y, where U = L^T
    vector<vector<double>> U(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            U[i][j] = L[j][i];

    vector<double> x = backSubstitution(U, y);

    printSolution(fout, x);
}