#ifndef LEASTSQUARE_HPP
#define LEASTSQUARE_HPP

#include "curvefitting.hpp"
#include <fstream>

class LeastSquare : public CurveFitting {
public:
    Matrix fit(int degree) override;
    double computeRMSE(const Matrix& coeffs);
    void outputTable(std::ofstream& fout, const Matrix& coeffs);
};

#endif