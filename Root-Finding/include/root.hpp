
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;
class root
{
public:
    double tol;
    int itr;

    root()
    {
        tol = 0.0001;
        itr= 0;
    }

    virtual double f(double x) = 0;
    virtual double solve() = 0;
};

class bisect : public root
{
public:
    double a, b;

    bisect();

    double f(double x);
    int findInterval();
    double solve();
};

class newton : public root
{
public:
    double x0;

    newton();

    double f(double x);
    double df(double x);
    double solve();
};

class fixedpoint : public root
{
public:
    double x0;

    fixedpoint(double x = 0.5);

    double f(double x);
    double g(double x);
    double solve();
};

