#include "crouts.hpp"
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

CroutLU::CroutLU(const Matrix &m) : LU(m) {}

void CroutLU::solve(ofstream &fout)
{
    int n = rows;

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        U[i][i] = 1;

    for (int j = 0; j < n; j++)
    {
        for (int i = j; i < n; i++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * U[k][j];
            L[i][j] = mat[i][j] - sum;
        }

        for (int i = j + 1; i < n; i++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[j][k] * U[k][i];
            if (L[j][j] == 0)
                throw logic_error("Division by zero in Crout LU");
            U[j][i] = (mat[j][i] - sum) / L[j][j];
        }
    }

    vector<double> b(n);
    for (int i = 0; i < n; i++)
        b[i] = mat[i][cols - 1];

    vector<double> y = forwardSubstitution(L, b);
    vector<double> x = backSubstitution(U, y);

    printSolution(fout, x);
}