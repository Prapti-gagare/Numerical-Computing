#ifndef GAUSS_SEIDEL_HPP
#define GAUSS_SEIDEL_HPP

#include "iterative_method.hpp"

class GaussSeidel : public IterativeMethod
{
public:
    GaussSeidel(const Matrix &m, int maxIter = 1000, double tol = 1e-6);
    void solve(ofstream &fout) override;
};

#endif