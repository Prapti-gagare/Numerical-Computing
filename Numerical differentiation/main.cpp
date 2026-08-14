#include "numerical_diff.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    double x = 1.0;

    vector<double> h =
    {
        1e-1,
        1e-2,
        1e-3,
        1e-4,
        1e-5,
        1e-6
    };

    TestFunction functions[] =
    {
        {"e^x", f1, df1},
        {"sin(x)", f2, df2},
        {"x^3 - 2x + 1", f3, df3}
    };

    cout << "====================================\n";
    cout << "NUMERICAL DIFFERENTIATION\n";
    cout << "====================================\n";
    cout << "Evaluation point: x = " << x << endl;

    for (const auto& func : functions)
    {
        runExperiment(func, x, h);
    }

    return 0;
}