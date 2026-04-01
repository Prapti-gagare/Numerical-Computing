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
    virtual vector<pair<double, double>> estimateEigenvalues() = 0;
    virtual void printEigenvalues(ofstream &fout) = 0;

protected:
    void assertSquare() const;
};

#endif