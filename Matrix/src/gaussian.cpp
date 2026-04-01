#include "gaussian.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include "matrix.hpp"
// ...existing code...
GaussianElimination::GaussianElimination(const Matrix &m) : LinearSystem(m) {}

void GaussianElimination::solve(ofstream &fout)
{
    int n = rows;
    if (cols != n + 1)
        throw logic_error("Matrix must be augmented");

    for (int k = 0; k < n - 1; k++)
    {
        int maxRow = k;
        for (int i = k + 1; i < n; i++)
            if (abs(mat[i][k]) > abs(mat[maxRow][k]))
                maxRow = i;

        if (mat[maxRow][k] == 0)
        {
            fout << "No unique solution.\n";
            return;
        }

        if (maxRow != k)
            swap(mat[k], mat[maxRow]);

        for (int i = k + 1; i < n; i++)
        {
            double factor = mat[i][k] / mat[k][k];
            for (int j = k; j < cols; j++)
                mat[i][j] -= factor * mat[k][j];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        if (mat[i][i] == 0)
            throw runtime_error("No unique solution.");

        x[i] = mat[i][n];
        for (int j = i + 1; j < n; j++)
            x[i] -= mat[i][j] * x[j];
        x[i] /= mat[i][i];
    }

    for (int i = 0; i < n; i++)
        fout << "x" << i + 1 << " = " << x[i] << endl;
}