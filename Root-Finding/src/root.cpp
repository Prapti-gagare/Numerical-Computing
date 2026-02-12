#include "../include/root.hpp"

bisect::bisect()
{
    a = 0;
    b = 0;
}

double bisect::f(double x)
{
    return x*x*x - x - 1;
}

int bisect::findInterval()
{
    double step = 0.05;

    for (int i = 0; i < 100; i++)
    {
        double left  = i * step;
        double right = left + step;

        if (f(left) * f(right) < 0)
        {
            a = left;
            b = right;
            return 1;
        }
    }
    return 0;
}

double bisect::solve()
{
    if (!findInterval())
        throw runtime_error("Bisection wrong interval");

    double m_prev = a;
    double m_curr;
    itr = 0;

    while (true)
    {
        m_curr = (a + b) / 2;
        itr++;

        if (fabs(m_curr - m_prev) < tol)
            return m_curr;

        if (f(a) * f(m_curr) < 0)
            b = m_curr;
        else
            a = m_curr;

        m_prev = m_curr;
    }
}

newton::newton()
{
    x0 = 1;  
}

double newton::f(double x)
{
    return x*x*x - x - 1;
}

double newton::df(double x)
{
    return 3*x*x - 1;
}

double newton::solve()
{
    double x1;
    itr = 0;

    while (itr < 1000)
    {
        if (fabs(df(x0)) < 0.000001)
            throw runtime_error("Small derivative");

        x1 = x0 - f(x0) / df(x0);
        itr++;

        if (fabs(x1 - x0) < tol)
            return x1;

        x0 = x1;
    }

    throw runtime_error("NewtonRaphson not converge");
}


fixedpoint::fixedpoint(double x)
{
    x0 = x;
}

double fixedpoint::f(double x)
{
    return x*x*x - x - 1;
}

double fixedpoint::g(double x)
{
    return cbrt(x + 1);

}


double fixedpoint::solve()
{
    double x1;
    itr = 0;

    while (itr< 1000)
    {
        x1 = g(x0);
        itr++;

        if (fabs(x1 - x0) < tol)
            return x1;

        x0 = x1;
    }

    throw runtime_error("Fixed Point not converge");
}
