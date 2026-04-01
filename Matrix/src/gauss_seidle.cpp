#include "gauss_seidle.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "matrix.hpp"
// ...existing code...
using namespace std;

GaussSeidel::GaussSeidel(const Matrix &m, int maxIter, double tol)
    : IterativeMethod(m, maxIter, tol) {}

void GaussSeidel::solve(ofstream &fout)
{
    int n = rows;
    if (cols != n + 1)
        throw runtime_error("Invalid augmented matrix: expected n rows and n+1 columns");

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

        double sumRow = 0.0;
        for (int j = 0; j < n; j++)
            if (j != i) sumRow += fabs(A[i][j]);
        if (fabs(A[i][i]) <= sumRow)
            A[i][i] = sumRow + 1e-5;
    }

    // Print diagonally dominant matrix (A | b)
    cout << "\n--- Gauss-Seidel: Matrix after making Diagonally Dominant ---\n";
    fout << "\n--- Gauss-Seidel: Matrix after making Diagonally Dominant ---\n";
    cout << fixed << setprecision(4);
    fout << fixed << setprecision(4);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "\t";
            fout << A[i][j] << "\t";
        }
        cout << "| " << b[i] << "\n";
        fout << "| " << b[i] << "\n";
    }
    cout << "-------------------------------------------------------------\n\n";
    fout << "-------------------------------------------------------------\n\n";

    vector<double> x(n, 0.0); 
    bool converged = false;

    for (int iter = 0; iter < maxIterations; iter++) {
        double error = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(A[i][i]) < 1e-15)
                throw runtime_error("Zero diagonal element at row " + to_string(i));

            double sum = b[i];
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum -= A[i][j] * x[j]; 

            double x_new = sum / A[i][i];
            error = max(error, fabs(x_new - x[i]));
            x[i] = x_new;
        }

        if (error < tolerance) {
            fout << "Gauss-Seidel converged in " << iter + 1
                 << " iterations (error = " << error << ")\n";
            converged = true;
            break;
        }
    }

    if (!converged)
        fout << "Warning: Gauss-Seidel did NOT converge in "
             << maxIterations << " iterations.\n";


             
    fout << fixed << setprecision(5);
    for (int i = 0; i < n; i++)
        fout << "x" << i + 1 << " = " << x[i]
             << " ≈ " << int(round(x[i])) << "\n";
}