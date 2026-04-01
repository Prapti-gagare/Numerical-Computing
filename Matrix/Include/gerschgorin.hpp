#ifndef GERSCHGORIN_HPP
#define GERSCHGORIN_HPP

#include "Eigenvalue.hpp"
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

// Gerschgorin Circle Theorem:
// For each row i, define a disk D_i centered at a_ii with radius:
//   r_i = sum of |a_ij| for all j != i
// Every eigenvalue lies in at least one disk D_i = (a_ii - r_i, a_ii + r_i)

class Gerschgorin : public EigenValue
{
public:
    Gerschgorin(const Matrix &m);

    // Compute Gerschgorin disks: returns vector of (center, radius) per row
    vector<pair<double, double>> computeDisks();

    // Returns eigenvalue bound intervals (center - radius, center + radius)
    vector<pair<double, double>> estimateEigenvalues() override;

    // Print all disks and overall eigenvalue bounds to fout and cout
    void printEigenvalues(ofstream &fout) override;

    // Overall bound: [global_min, global_max] across all disks
    pair<double, double> globalBounds();
};

#endif