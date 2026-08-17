#ifndef NUMERICAL_DIFFERENTIATION_HPP
#define NUMERICAL_DIFFERENTIATION_HPP

#include <string>

using namespace std;

typedef double (*MathFunction)(double);

class TestFunction {
private:
    string name;
    MathFunction function;
    MathFunction exactDerivative;

public:
    TestFunction(
        const string& name,
        MathFunction function,
        MathFunction exactDerivative
    );

    string getName() const;
    double evaluate(double x) const;
    double exact(double x) const;
};
class DifferenceMethod {
protected:
    string methodName;

public:
    DifferenceMethod(const string& name);
    string getName() const;
    virtual double derivative(const TestFunction& f, double x, double h) const = 0;
};
class ForwardDifference : public DifferenceMethod {
public:
    ForwardDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};
class BackwardDifference : public DifferenceMethod {
public:
    BackwardDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};
class CentralDifference : public DifferenceMethod {
public:
    CentralDifference();
    double derivative(const TestFunction& f, double x, double h) const override;
};

#endif