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

void runMethod(
    const TestFunction& f,
    DifferenceMethod& method,
    double x,
    double exactValue,
    const vector<double>& hValues,
    ofstream& csv
) {
    cout << "\nMethod: " << method.getName() << "\n";
    cout << setw(12) << "h"
         << setw(20) << "Approximation"
         << setw(20) << "Absolute Error" << "\n";

    for (double h : hValues) {
        double approx = method.derivative(f, x, h);
        double error = fabs(exactValue - approx);

        cout << scientific << setprecision(6)
             << setw(12) << h
             << setw(20) << approx
             << setw(20) << error << "\n";

        csv << f.getName() << ","
            << method.getName() << ","
            << scientific << setprecision(12) << h << ","
            << approx << ","
            << exactValue << ","
            << error << "\n";
    }
    cout << fixed;
}

int main() {
    const double x = 1.0;
    int numH = 0;
    cout << "Enter the number of step sizes (h values) to test: ";
    cin >> numH;

    while (numH <= 0) {
        cout << "Please enter a positive integer: ";
        cin >> numH;
    }

    vector<double> hValues(numH);
    for (int i = 0; i < numH; ++i) {
        cout << "Enter h[" << (i + 1) << "]: ";
        cin >> hValues[i];
    }
    cout << "\n";
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

    ForwardDifference forward;
    BackwardDifference backward;
    CentralDifference central;

    ofstream csv("results.csv");

    if (!csv) {
        cout << "Error: Could not create results.csv\n";
        return 1;
    }

    cout << fixed << setprecision(10);
    cout << "Evaluation point x = " << x << "\n\n";

    for (const TestFunction& f : functions) {
        double exactValue = f.exact(x);

        cout << "============================================================\n";
        cout << "Function: " << f.getName() << "\n";
        cout << "Exact derivative at x=1: " << exactValue << "\n";
        cout << "============================================================\n";

        runMethod(f, forward, x, exactValue, hValues, csv);
        runMethod(f, backward, x, exactValue, hValues, csv);
        runMethod(f, central, x, exactValue, hValues, csv);

        cout << "\n";
    }

    csv.close();

    cout << "\nResults have been saved to results.csv\n";

    return 0;
}