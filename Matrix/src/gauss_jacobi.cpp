#include "gauss_jacobi.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "matrix.hpp"

using namespace std;

GaussJacobi::GaussJacobi(const Matrix &m, int maxIter, double tol)
    : IterativeMethod(m, maxIter, tol) {}

void GaussJacobi::solve(ofstream &fout)
{
    int n = rows;
    if (cols != n + 1)
        throw runtime_error("Invalid augmented matrix: expected n rows and n+1 columns");
    Matrix coeffOnly(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            coeffOnly.set(i, j, mat[i][j]);

    Matrix domCoeff = coeffOnly.makeDiagonallyDominant();

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    for (int i = 0; i < n; i++) {
        b[i] = mat[i][n];
        for (int j = 0; j < n; j++)
            A[i][j] = mat[i][j];
    }
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        double maxVal = fabs(A[i][i]);
        for (int k = i + 1; k < n; k++)
            if (fabs(A[k][i]) > maxVal) { maxVal = fabs(A[k][i]); maxRow = k; }
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }
    }
    for (int i = 0; i < n; i++)
        A[i][i] = domCoeff.get(i, i);

    fout << "\nMatrix after making Diagonally Dominant:\n";
    fout << fixed << setprecision(4);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fout << A[i][j] << "\t";
        fout << "| " << b[i] << "\n";
    }

    // --- Gauss-Jacobi iteration ---
    vector<double> x(n, 0.0);
    vector<double> x_new(n, 0.0);
    bool converged = false;

    for (int iter = 0; iter < maxIterations; iter++) {
        for (int i = 0; i < n; i++) {
            if (fabs(A[i][i]) < 1e-15)
                throw runtime_error("Zero diagonal element at row " + to_string(i));

            double sum = b[i];
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum -= A[i][j] * x[j];   // uses OLD x (Jacobi)

            x_new[i] = sum / A[i][i];
        }

        double error = 0.0;
        for (int i = 0; i < n; i++)
            error = max(error, fabs(x_new[i] - x[i]));

        x = x_new;

        if (error < tolerance) {
            fout << "Gauss-Jacobi converged in " << iter + 1
                 << " iterations (error = " << error << ")\n";
            converged = true;
            break;
        }
    }

    if (!converged)
        fout << "Warning: Gauss-Jacobi did NOT converge in "
             << maxIterations << " iterations.\n";

    fout << fixed << setprecision(5);
    for (int i = 0; i < n; i++)
        fout << "x" << i + 1 << " = " << x[i]
             << " ≈ " << int(round(x[i])) << "\n";
}