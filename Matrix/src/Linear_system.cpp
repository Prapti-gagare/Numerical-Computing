#include "LinearSystem.hpp"
#include <fstream>
#include <iostream>

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

    if (rL != rR || cR != 1)
        throw runtime_error("Dimension mismatch.");

    fout << rL << " " << (cL + 1) << endl;

    for (int i = 0; i < rL; i++)
    {
        for (int j = 0; j < cL; j++)
        {
            double val;
            finL >> val;
            fout << val << " ";
        }

        double rhs;
        finR >> rhs;

        fout << rhs << endl;
    }

    cout << "Augmented matrix saved to " << outputFile << endl;
}