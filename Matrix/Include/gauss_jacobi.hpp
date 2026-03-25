#ifndef GAUSS_JACOBI_HPP
#define GAUSS_JACOBI_HPP

#include "iterative_method.hpp"

class GaussJacobi : public IterativeMethod
{
public:
    GaussJacobi(const Matrix &m, int maxIter = 1000, double tol = 1e-6);

    void solve(ofstream &fout);
};

#endif