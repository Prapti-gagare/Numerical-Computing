#ifndef NUMERICAL_DIFF_HPP
#define NUMERICAL_DIFF_HPP

#include <string>
#include <vector>

using Function = double (*)(double);

struct TestFunction
{
    std::string name;
    Function f;
    Function exactDerivative;
};

// Test functions
double f1(double x);
double df1(double x);

double f2(double x);
double df2(double x);

double f3(double x);
double df3(double x);

// Difference formulas
double forwardDifference(Function f, double x, double h);
double backwardDifference(Function f, double x, double h);
double centralDifference(Function f, double x, double h);

// Error and convergence
double absoluteError(double approximate, double exact);
double observedOrder(double error1, double error2);

// Experiment
void runExperiment(const TestFunction& func,
                   double x,
                   const std::vector<double>& hValues);

#endif