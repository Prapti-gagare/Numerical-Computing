#ifndef NUMERICAL_DIFFERENTIATION_HPP
#define NUMERICAL_DIFFERENTIATION_HPP

#include <string>
#include <vector>
#include <functional>

// Stores one test function and its exact first derivative.
class TestFunction {
private:
    std::string name;
    std::function<double(double)> function;
    std::function<double(double)> exactDerivative;

public:
    TestFunction(
        const std::string& name,
        std::function<double(double)> function,
        std::function<double(double)> exactDerivative
    );

    std::string getName() const;
    double evaluate(double x) const;
    double exact(double x) const;
};

// Abstract base class for all finite-difference methods.
class DifferenceMethod {
protected:
    std::string methodName;

public:
    DifferenceMethod(const std::string& name);
    virtual ~DifferenceMethod() = default;

    std::string getName() const;

    // Polymorphic function: every method implements its own formula.
    virtual double derivative(const TestFunction& f, double x, double h) const = 0;
};

// Forward difference:
// f'(x) ≈ [f(x+h) - f(x)] / h
class ForwardDifference : public DifferenceMethod {
public:
    ForwardDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};

// Backward difference:
// f'(x) ≈ [f(x) - f(x-h)] / h
class BackwardDifference : public DifferenceMethod {
public:
    BackwardDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};

// Central difference:
// f'(x) ≈ [f(x+h) - f(x-h)] / (2h)
class CentralDifference : public DifferenceMethod {
public:
    CentralDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};

#endif
