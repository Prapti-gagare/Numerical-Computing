#include "LinearSystem.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "matrix.hpp"
using namespace std;

LinearSystem::LinearSystem() : Matrix() {}

LinearSystem::LinearSystem(const Matrix &m) : Matrix(m) {}

void LinearSystem::generateAugmentedMatrixFile(
    const string &leftFile,
    const string &rightFile,
    const string &outputFile)
{
    ifstream finL(leftFile);
    ifstream finR(rightFile);
    ofstream fout(outputFile);

    if (!finL || !finR || !fout)
        throw runtime_error("File opening error.");

    int rL, cL, rR, cR;
    finL >> rL >> cL;
    finR >> rR >> cR;

    if (rL != rR)
        throw runtime_error("Row count mismatch between left and right files.");
    if (cR != 1)
        throw runtime_error("Right-hand side file must have exactly 1 column.");
    fout << rL << " " << (cL + 1) << "\n";

    for (int i = 0; i < rL; i++)
    {
        for (int j = 0; j < cL; j++)
        {
            double val;
            if (!(finL >> val))
                throw runtime_error("Unexpected end of left matrix file at row " + to_string(i));
            fout << val << " ";
        }

        double rhs;
        if (!(finR >> rhs))
            throw runtime_error("Unexpected end of right matrix file at row " + to_string(i));
        fout << rhs << "\n";
    }

    cout << "Augmented matrix saved to " << outputFile << "\n";
}