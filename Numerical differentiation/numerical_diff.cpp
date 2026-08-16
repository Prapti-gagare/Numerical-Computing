#include "numerical_diff.hpp"

// ---------------- TestFunction ----------------

TestFunction::TestFunction(
    const std::string& name,
    std::function<double(double)> function,
    std::function<double(double)> exactDerivative
)
    : name(name), function(function), exactDerivative(exactDerivative) {}

std::string TestFunction::getName() const {
    return name;
}

double TestFunction::evaluate(double x) const {
    return function(x);
}

double TestFunction::exact(double x) const {
    return exactDerivative(x);
}

// ---------------- DifferenceMethod ----------------

DifferenceMethod::DifferenceMethod(const std::string& name)
    : methodName(name) {}

std::string DifferenceMethod::getName() const {
    return methodName;
}

// ---------------- ForwardDifference ----------------

ForwardDifference::ForwardDifference()
    : DifferenceMethod("Forward") {}

double ForwardDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x + h) - f.evaluate(x)) / h;
}

// ---------------- BackwardDifference ----------------

BackwardDifference::BackwardDifference()
    : DifferenceMethod("Backward") {}

double BackwardDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x) - f.evaluate(x - h)) / h;
}

// ---------------- CentralDifference ----------------

CentralDifference::CentralDifference()
    : DifferenceMethod("Central") {}

double CentralDifference::derivative(
    const TestFunction& f, double x, double h
) const {
    return (f.evaluate(x + h) - f.evaluate(x - h)) / (2.0 * h);
}