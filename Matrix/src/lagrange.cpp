#include "lagrange.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <sstream>

using namespace std;
Lagrange::Lagrange() : Interpolation() {}

Lagrange::Lagrange(const Matrix &m) : Interpolation(m) {}
double Lagrange::basisPolynomial(int i, double x, ofstream &fout) const
{
    int n = rows;
    if (i < 0 || i >= n)
        throw out_of_range("Lagrange::basisPolynomial: index i out of range.");

    double xi = mat[i][0];

    fout << "  L_" << i << "(x) = ";
    double num = 1.0, den = 1.0;
    bool firstFactor = true;

    for (int j = 0; j < n; j++)
    {
        if (j == i) continue;
        double xj = mat[j][0];

        num *= (x   - xj);
        den *= (xi  - xj);

        if (!firstFactor) fout << " * ";
        fout << "(x - " << xj << ")";
        firstFactor = false;
    }

    fout << "\n        / ";
    firstFactor = true;
    for (int j = 0; j < n; j++)
    {
        if (j == i) continue;
        double xj = mat[j][0];
        if (!firstFactor) fout << " * ";
        fout << "(" << xi << " - " << xj << ")";
        firstFactor = false;
    }

    double Li = (fabs(den) < 1e-15) ? 0.0 : num / den;

    fout << "\n        = " << num << " / " << den
         << " = " << Li << "\n";

    return Li;
}

vector<double> Lagrange::allBasisValues(double x) const
{
    int n = rows;
    vector<double> L(n, 1.0);
    for (int i = 0; i < n; i++)
    {
        double xi = mat[i][0];
        for (int j = 0; j < n; j++)
        {
            if (j == i) continue;
            double xj = mat[j][0];
            double den = xi - xj;
            if (fabs(den) < 1e-15)
                throw runtime_error("Lagrange: duplicate x values at indices "
                                    + to_string(i) + " and " + to_string(j));
            L[i] *= (x - xj) / den;
        }
    }
    return L;
}

double Lagrange::interpolate(double xQuery, ofstream &fout)
{
    validateDataPoints();
    int n = rows;
    fout << "       Lagrange Interpolation\n";
    fout << "Query point: x = " << xQuery << "\n\n";

    printDataPoints(fout);

    for (int i = 0; i < n; i++)
        if (fabs(mat[i][0] - xQuery) < 1e-12)
        {
            fout << "x = " << xQuery
                 << " is a data node. Exact value = " << mat[i][1] << "\n";
            return mat[i][1];
        }

    fout << "Formula:  P(x) = sum of [ y_i * L_i(x) ]  for i = 0 to " << n-1 << "\n\n";

    double result = 0.0;

    fout << fixed << setprecision(6);
    fout << "--- Computing basis polynomials at x = " << xQuery << " ---\n\n";

    for (int i = 0; i < n; i++)
    {
        double Li = basisPolynomial(i, xQuery, fout);
        double yi = mat[i][1];
        double term = yi * Li;

        fout << "  y_" << i << " * L_" << i << "(" << xQuery << ")"
             << " = " << yi << " * " << Li
             << " = " << term << "\n\n";

        result += term;
    }

    double sumL = 0.0;
    auto Lvals = allBasisValues(xQuery);
    for (double v : Lvals) sumL += v;

    fout << "--- Summary ---\n";
    fout << "Sum of all L_i (should be 1.0): " << sumL << "\n\n";
fout << "Contribution of each term:\n\n";
for (int i = 0; i < n; i++)
{
    double yi = mat[i][1];
    double Li = Lvals[i];
    double term = yi * Li;

    fout << "i = " << i
         << " : y_" << i << " = " << yi
         << ", L_" << i << "(x) = " << Li
         << ", y_" << i << " * L_" << i << "(x) = " << term << "\n";
}
fout << "\n";
    
    fout << "  P(" << xQuery << ") = " << result << "\n";

    return result;
}