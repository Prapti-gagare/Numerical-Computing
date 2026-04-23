#include "curvefitting.hpp"
using namespace std;
CurveFitting::CurveFitting() : Matrix() {}

void CurveFitting::setData(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) {
        rows = 0;
        cols = 0;
        mat.clear();
        return;
    }
    rows = x.size();
    cols = 2;
    mat.resize(rows,vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        mat[i][0] = x[i];
        mat[i][1] = y[i];
    }
}