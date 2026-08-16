#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include "numerical_diff.hpp"

using namespace std;

double expFunction(double x)
{
    return exp(x);
}

double expDerivative(double x)
{
    return exp(x);
}

double sinFunction(double x)
{
    return sin(x);
}

double sinDerivative(double x)
{
    return cos(x);
}

double polynomialFunction(double x)
{
    return x * x * x - 2 * x + 1;
}

double polynomialDerivative(double x)
{
    return 3 * x * x - 2;
}

int main() {
    const double x = 1.0;

    // Six step sizes required by the assignment.
    vector<double> hValues = {
        1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6
    };

    // Test functions and their exact first derivatives.
    vector<TestFunction> functions = {
        TestFunction(
            "exp(x)",
            expFunction,
            expDerivative
        ),

        TestFunction(
            "sin(x)",
            sinFunction,
            sinDerivative
        ),

        TestFunction(
            "x^3 - 2x + 1",
            polynomialFunction,
            polynomialDerivative
        )
    };

    // OOP: objects of derived classes are accessed through base-class pointers.
    ForwardDifference forward;
    BackwardDifference backward;
    CentralDifference central;

    vector<DifferenceMethod*> methods = {
        &forward, &backward, &central
    };

    // CSV file can be used directly for the log-log plot.
    ofstream csv("results.csv");

    if (!csv) {
        cerr << "Error: Could not create results.csv\n";
        return 1;
    }

    csv << "Function,Method,h,Approximation,Exact,AbsoluteError\n";

    cout << fixed << setprecision(10);

    cout << "NUMERICAL DIFFERENTIATION USING OOP\n";
    cout << "Evaluation point x = " << x << "\n\n";

    for (const TestFunction& f : functions) {
        double exactValue = f.exact(x);

        cout << "============================================================\n";
        cout << "Function: " << f.getName() << "\n";
        cout << "Exact derivative at x=1: " << exactValue << "\n";
        cout << "============================================================\n";

        for (DifferenceMethod* method : methods) {
            cout << "\nMethod: " << method->getName() << "\n";
            cout << setw(12) << "h"
                 << setw(20) << "Approximation"
                 << setw(20) << "Absolute Error" << "\n";

            for (double h : hValues) {
                double approx = method->derivative(f, x, h);
                double error = fabs(exactValue - approx);

                cout << scientific << setprecision(6)
                     << setw(12) << h
                     << setw(20) << approx
                     << setw(20) << error << "\n";

                csv << f.getName() << ","
                    << method->getName() << ","
                    << scientific << setprecision(12) << h << ","
                    << approx << ","
                    << exactValue << ","
                    << error << "\n";
            }
            cout << fixed;
        }
        cout << "\n";
    }

    csv.close();

    cout << "\nResults have been saved to results.csv\n";

    cout << "\nSYMBOLIC RESULT FOR f(x) = x^3 - 2x + 1\n";
    cout << "f'(x) = 3x^2 - 2\n";
    cout << "At x = 1: f'(1) = 1\n\n";

    cout << "Forward difference at x=1:\n";
    cout << "D_f = 1 + 3h + h^2\n";
    cout << "Absolute error = 3h + h^2\n\n";

    cout << "Backward difference at x=1:\n";
    cout << "D_b = 1 - 3h + h^2\n";
    cout << "Absolute error = 3h - h^2  (for the small h values used)\n\n";

    cout << "Central difference at x=1:\n";
    cout << "D_c = 1 + h^2\n";
    cout << "Absolute error = h^2\n\n";

    cout << "Expected order of accuracy:\n";
    cout << "Forward  : O(h)\n";
    cout << "Backward : O(h)\n";
    cout << "Central  : O(h^2)\n";

    return 0;
}