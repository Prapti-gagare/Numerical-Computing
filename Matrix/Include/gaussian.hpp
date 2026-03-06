#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include "LinearSystem.hpp"

class GaussianElimination : public LinearSystem
{
public:
    GaussianElimination(const Matrix &m);
    void solve(ofstream &fout);
};

#endif