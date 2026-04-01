#include "iterative_method.hpp"
#include "matrix.hpp"

IterativeMethod::IterativeMethod(const Matrix &m, int maxIter, double tol)
    : LinearSystem(m), maxIterations(maxIter), tolerance(tol) {}

vector<vector<double>> IterativeMethod::extractA() const
{
    vector<vector<double>> A(rows, vector<double>(cols - 1));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols - 1; j++)
            A[i][j] = mat[i][j];
    return A;
}
vector<double> IterativeMethod::extractB() const
{
    vector<double> b(rows);
    for (int i = 0; i < rows; i++)
        b[i] = mat[i][cols - 1];
    return b;
}

void IterativeMethod::printSolution(ofstream &fout, const vector<double> &x)
{
    fout << "Solution:\n";
    for (int i = 0; i < (int)x.size(); i++)
        fout << "x" << i + 1 << " = " << x[i] << "\n";
}