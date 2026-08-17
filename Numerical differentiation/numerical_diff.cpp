#include "numerical_diff.hpp"

using namespace std;

TestFunction::TestFunction(
    const string& name,
    MathFunction function,
    MathFunction exactDerivative
)
    : name(name), function(function), exactDerivative(exactDerivative) {}

string TestFunction::getName() const {
    return name;
}

double TestFunction::evaluate(double x) const {
    return function(x);
}

double TestFunction::exact(double x) const {
    return exactDerivative(x);
}



DifferenceMethod::DifferenceMethod(const string& name)
    : methodName(name) {}

string DifferenceMethod::getName() const {
    return methodName;
}


ForwardDifference::ForwardDifference()
    : DifferenceMethod("Forward") {}

double ForwardDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x + h) - f.evaluate(x)) / h;
}

BackwardDifference::BackwardDifference()
    : DifferenceMethod("Backward") {}

double BackwardDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x) - f.evaluate(x - h)) / h;
}

CentralDifference::CentralDifference()
    : DifferenceMethod("Central") {}

double CentralDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x + h) - f.evaluate(x - h)) / (2.0 * h);
}