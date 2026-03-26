#include "gauss_jacobi.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

GaussJacobi::GaussJacobi(const Matrix &m, int maxIter, double tol)
    : IterativeMethod(m, maxIter, tol) {}

void GaussJacobi::solve(ofstream &fout)
{
    int n = rows;
    if (cols != n + 1)
        throw runtime_error("Invalid augmented matrix: expected n rows and n+1 columns");

    // Step 1: Extract A and b from augmented matrix
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = mat[i][n];
        for (int j = 0; j < n; j++)
            A[i][j] = mat[i][j];
    }

    // Step 2: Improve diagonal dominance with row permutation
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        double maxVal = fabs(A[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > maxVal) {
                maxVal = fabs(A[k][i]);
                maxRow = k;
            }
        }
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }

        // Ensure strict diagonal dominance
        double sumRow = 0.0;
        for (int j = 0; j < n; j++)
            if (j != i) sumRow += fabs(A[i][j]);
        if (fabs(A[i][i]) <= sumRow)
            A[i][i] = sumRow + 1e-5; // tiny shift
    }

    // Step 3: Initialize Jacobi iteration
    vector<double> x(n, 0.0);      // previous iteration
    vector<double> x_new(n, 0.0);  // current iteration
    bool converged = false;

    for (int iter = 0; iter < maxIterations; iter++) {
        for (int i = 0; i < n; i++) {
            if (fabs(A[i][i]) < 1e-15)
                throw runtime_error("Zero diagonal element at row " + to_string(i));

            double sum = b[i];
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum -= A[i][j] * x[j]; // use OLD values for Jacobi

            x_new[i] = sum / A[i][i];
        }

        // Compute max error for convergence
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

    // Step 4: Print solution with decimal and rounded integer
    fout << fixed << setprecision(5);
    for (int i = 0; i < n; i++)
        fout << "x" << i + 1 << " = " << x[i]
             << " ≈ " << int(round(x[i])) << "\n";
}