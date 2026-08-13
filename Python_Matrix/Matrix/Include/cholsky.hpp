#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP

#include "lu.hpp"

using namespace std;

class CholeskyDecomposition : public LU
{
public:
    CholeskyDecomposition(const Matrix &m);
    void solve(ofstream &fout);
};

#endif