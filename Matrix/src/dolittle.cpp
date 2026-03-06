#include "dolittle.hpp"
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

DolittleLU::DolittleLU(const Matrix &m) : LU(m) {}

void DolittleLU::solve(ofstream &fout)
{
    int n = rows;

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    
    for (int i = 0; i < n; i++)
        L[i][i] = 1;

    for (int i = 0; i < n; i++)
    {
        
        for (int j = i; j < n; j++)
        {
            double sum = 0;

            for (int k = 0; k < i; k++)
                sum += L[i][k] * U[k][j];

            U[i][j] = mat[i][j] - sum;
        }

        for (int j = i + 1; j < n; j++)
        {
            double sum = 0;

            for (int k = 0; k < i; k++)
                sum += L[j][k] * U[k][i];

            if (U[i][i] == 0)
                throw logic_error("Division by zero in Doolittle");

            L[j][i] = (mat[j][i] - sum) / U[i][i];
        }
    }

    vector<double> b(n);
    for (int i = 0; i < n; i++)
        b[i] = mat[i][cols - 1];

    vector<double> y = forwardSubstitution(L, b);
    vector<double> x = backSubstitution(U, y);

    printSolution(fout, x);
}