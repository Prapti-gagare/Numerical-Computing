#ifndef LAGRANGE_HPP
#define LAGRANGE_HPP

#include "interpolation.hpp"
#include <vector>
#include <fstream>

using namespace std;

class Lagrange : public Interpolation
{
public:
    Lagrange();
    explicit Lagrange(const Matrix &m);   
    double basisPolynomial(int i, double x, ofstream &fout) const;
    vector<double> allBasisValues(double x) const;
    double interpolate(double xQuery, ofstream &fout) override;
};

#endif 