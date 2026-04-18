#ifndef CURVEFITTING_HPP
#define CURVEFITTING_HPP

#include "matrix.hpp"
#include <vector>
using namespace std;
class CurveFitting : public Matrix {
public:
    CurveFitting();
    void setData(const vector<double>& x, const vector<double>& y);
    virtual Matrix fit(int degree) = 0;
};

#endif