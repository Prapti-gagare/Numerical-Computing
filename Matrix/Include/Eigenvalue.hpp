#ifndef EIGENVALUE_HPP
#define EIGENVALUE_HPP

#include "matrix.hpp"
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

class EigenValue : public Matrix
{
public:
    EigenValue();
    EigenValue(const Matrix &m);

    // Returns estimated eigenvalue bounds as a vector of (min, max) intervals
    virtual vector<pair<double, double>> estimateEigenvalues() = 0;

    // Print eigenvalue estimates to file and console
    virtual void printEigenvalues(ofstream &fout) = 0;

protected:
    // Check matrix is square before any computation
    void assertSquare() const;
};

#endif