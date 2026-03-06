#include "lu.hpp"
#include <vector>
#include <fstream>

using namespace std;

LU::LU(const Matrix &m) : LinearSystem(m) {}

vector<double> LU::forwardSubstitution(vector<vector<double>> &L,vector<double> &b)
{
    int n = rows;
    vector<double> y(n);

    for (int i = 0; i < n; i++)
    {
        double sum = 0;

        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];

        y[i] = (b[i] - sum) / L[i][i];
    }

    return y;
}

vector<double> LU::backSubstitution(vector<vector<double>> &U,vector<double> &y)
{
    int n = rows;
    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;

        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * x[j];

        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}

void LU::printSolution(
    ofstream &fout,
    vector<double> &x)
{
    fout << "Solution:\n";

    for (int i = 0; i < rows; i++)
        fout << "x" << i + 1 << " = " << x[i] << endl;
}