#include "numerical_diff.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;


// ============================================================
// TEST FUNCTIONS
// ============================================================

double f1(double x)
{
    return exp(x);
}

double df1(double x)
{
    return exp(x);
}


double f2(double x)
{
    return sin(x);
}

double df2(double x)
{
    return cos(x);
}


double f3(double x)
{
    return x*x*x - 2*x + 1;
}

double df3(double x)
{
    return 3*x*x - 2;
}


// ============================================================
// DIFFERENCE FORMULAS
// ============================================================

double forwardDifference(Function f, double x, double h)
{
    return (f(x+h) - f(x)) / h;
}

double backwardDifference(Function f, double x, double h)
{
    return (f(x) - f(x-h)) / h;
}

double centralDifference(Function f, double x, double h)
{
    return (f(x+h) - f(x-h)) / (2*h);
}


// ============================================================
// ERROR AND ORDER
// ============================================================

double absoluteError(double approximate, double exact)
{
    return fabs(approximate - exact);
}

double observedOrder(double e1, double e2)
{
    return log(e1/e2) / log(10.0);
}


// ============================================================
// RUN EXPERIMENT
// ============================================================

void runExperiment(const TestFunction& func,
                   double x,
                   const vector<double>& h)
{
    vector<double> ef, eb, ec;

    cout << "\n\nFunction: " << func.name << endl;
    cout << "Exact derivative = "
         << func.exactDerivative(x) << "\n\n";

    cout << scientific << setprecision(4);

    cout << setw(12) << "h"
         << setw(18) << "Forward Error"
         << setw(18) << "Backward Error"
         << setw(18) << "Central Error" << endl;

    cout << string(66, '-') << endl;

    for (double value : h)
    {
        double exact = func.exactDerivative(x);

        double a = absoluteError(
            forwardDifference(func.f, x, value), exact);

        double b = absoluteError(
            backwardDifference(func.f, x, value), exact);

        double c = absoluteError(
            centralDifference(func.f, x, value), exact);

        ef.push_back(a);
        eb.push_back(b);
        ec.push_back(c);

        cout << setw(12) << value
             << setw(18) << a
             << setw(18) << b
             << setw(18) << c << endl;
    }

    cout << "\nObserved Order of Convergence:\n";

    for (int i = 1; i < h.size(); i++)
    {
        cout << "h = " << h[i]
             << "  F = "
             << observedOrder(ef[i-1], ef[i])
             << "  B = "
             << observedOrder(eb[i-1], eb[i])
             << "  C = "
             << observedOrder(ec[i-1], ec[i])
             << endl;
    }
}