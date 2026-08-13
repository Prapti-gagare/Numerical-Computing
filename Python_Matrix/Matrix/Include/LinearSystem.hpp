#ifndef LINEAR_SYSTEM_HPP
#define LINEAR_SYSTEM_HPP

#include "matrix.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class LinearSystem : public Matrix
{
public:
    LinearSystem();
    LinearSystem(const Matrix &m);

    virtual void solve(ofstream &fout) = 0;
    void generateAugmentedMatrixFile(
        const string &leftFile,
        const string &rightFile,
        const string &outputFile);
};

#endif