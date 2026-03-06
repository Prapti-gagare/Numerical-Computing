#ifndef LINEAR_SYSTEM_HPP
#define LINEAR_SYSTEM_HPP

#include "matrix.hpp"
#include <fstream>

class LinearSystem : public Matrix
{
public:
    LinearSystem();
    LinearSystem(const Matrix &m);

    virtual void solve(std::ofstream &fout) = 0;

    // Augmented matrix function
    void generateAugmentedMatrixFile(
        const string &leftFile,
        const string &rightFile,
        const string &outputFile
    );
};

#endif