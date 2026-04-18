#include "leastsquare.hpp"
#include <cmath>
#include <fstream>

Matrix LeastSquare::fit(int degree) {
    int n = rows;
    if (n == 0 || degree < 0 || n <= degree) return Matrix();
    
    // Create design matrix A: n rows, degree+1 columns
    Matrix A(n, degree + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= degree; j++) {
            A.set(i, j, pow(mat[i][0], j));
        }
    }
    
    // Create y vector: n x 1
    Matrix Y(n, 1);
    for (int i = 0; i < n; i++) {
        Y.set(i, 0, mat[i][1]);
    }
    
    // Normal equations: A^T A x = A^T y
    Matrix AT = A.transpose();
    Matrix ATA = AT * A;
    Matrix ATY = AT * Y;
    
    // Solve for coefficients: x = (A^T A)^-1 * (A^T y)
    Matrix coeffs = ATA.inverse() * ATY;
    
    return coeffs;
}

double LeastSquare::computeRMSE(const Matrix& coeffs) {
    int n = rows;
    int degree = coeffs.getRows() - 1;
    double sum_sq_err = 0.0;
    for (int i = 0; i < n; i++) {
        double x = mat[i][0];
        double y = mat[i][1];
        double fi = 0.0;
        for (int j = 0; j <= degree; j++) {
            fi += coeffs.get(j, 0) * pow(x, j);
        }
        double err = fi - y;
        sum_sq_err += err * err;
    }
    return sqrt(sum_sq_err / n);
}

void LeastSquare::outputTable(std::ofstream& fout, const Matrix& coeffs) {
    int degree = coeffs.getRows() - 1;
    if (degree != 1) {
        fout << "Table output is designed for linear regression (degree 1).\n";
        return;
    }
    double a = coeffs.get(1, 0);
    double b = coeffs.get(0, 0);
    fout << "\nLeast Squares Table:\n";
    fout << "x\t\ty\t\tx^2\t\txy\t\tfi=ax+b\t\t(fi-y)^2\n";
    double sum_x2 = 0, sum_xy = 0, sum_fi_y2 = 0;
    for (int i = 0; i < rows; i++) {
        double x = mat[i][0];
        double y = mat[i][1];
        double x2 = x * x;
        double xy = x * y;
        double fi = a * x + b;
        double fi_y2 = (fi - y) * (fi - y);
        fout << x << "\t\t" << y << "\t\t" << x2 << "\t\t" << xy << "\t\t" << fi << "\t\t" << fi_y2 << "\n";
        sum_x2 += x2;
        sum_xy += xy;
        sum_fi_y2 += fi_y2;
    }
    fout << "Sums:\t\t\t" << sum_x2 << "\t\t" << sum_xy << "\t\t\t\t" << sum_fi_y2 << "\n";
}