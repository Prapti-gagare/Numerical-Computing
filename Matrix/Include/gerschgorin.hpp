#ifndef GERSCHGORIN_HPP
#define GERSCHGORIN_HPP

#include "Eigenvalue.hpp"
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

class Gerschgorin : public EigenValue
{
public:
    Gerschgorin(const Matrix &m);
    vector<pair<double, double>> computeDisks();
    vector<pair<double, double>> estimateEigenvalues() override;
    void printEigenvalues(ofstream &fout) override;
    pair<double, double> globalBounds();
};

#endif