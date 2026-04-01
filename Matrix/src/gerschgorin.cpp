#include "gerschgorin.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

Gerschgorin::Gerschgorin(const Matrix &m) : EigenValue(m) {}

// Compute disk for each row i:
//   center  = a_ii  (diagonal entry)
//   radius  = sum of |a_ij| for j != i  (off-diagonal sum)
vector<pair<double, double>> Gerschgorin::computeDisks()
{
    assertSquare();
    int n = rows;
    vector<pair<double, double>> disks(n); // (center, radius)

    for (int i = 0; i < n; i++)
    {
        double center = mat[i][i];
        double radius = 0.0;

        for (int j = 0; j < n; j++)
            if (j != i)
                radius += fabs(mat[i][j]);

        disks[i] = {center, radius};
    }

    return disks;
}

// Returns intervals (center - radius, center + radius) for each disk
vector<pair<double, double>> Gerschgorin::estimateEigenvalues()
{
    auto disks = computeDisks();
    int n = rows;
    vector<pair<double, double>> intervals(n);

    for (int i = 0; i < n; i++)
    {
        double lo = disks[i].first - disks[i].second;
        double hi = disks[i].first + disks[i].second;
        intervals[i] = {lo, hi};
    }

    return intervals;
}

// Global eigenvalue bounds: smallest lower bound and largest upper bound
pair<double, double> Gerschgorin::globalBounds()
{
    auto intervals = estimateEigenvalues();
    double globalMin = intervals[0].first;
    double globalMax = intervals[0].second;

    for (auto &interval : intervals)
    {
        if (interval.first  < globalMin) globalMin = interval.first;
        if (interval.second > globalMax) globalMax = interval.second;
    }

    return {globalMin, globalMax};
}

// Print full Gerschgorin analysis to both console and file
void Gerschgorin::printEigenvalues(ofstream &fout)
{
    assertSquare();
    int n = rows;

    auto disks     = computeDisks();
    auto intervals = estimateEigenvalues();
    auto bounds    = globalBounds();

    // Header
    cout << "\n========== Gerschgorin Circle Theorem ==========\n";
    fout << "\n========== Gerschgorin Circle Theorem ==========\n";

    cout << "Matrix (" << n << "x" << n << "):\n" << *this;
    fout << "Matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fout << mat[i][j] << " ";
        fout << "\n";
    }

    cout << "\n--- Gerschgorin Disks ---\n";
    fout << "\n--- Gerschgorin Disks ---\n";

    cout << fixed << setprecision(4);
    fout << fixed << setprecision(4);

    for (int i = 0; i < n; i++)
    {
        double center = disks[i].first;
        double radius = disks[i].second;
        double lo     = intervals[i].first;
        double hi     = intervals[i].second;

        // Off-diagonal sum detail
        cout << "D" << i+1 << ": center = a[" << i+1 << "][" << i+1 << "] = "
             << center << ",  radius r" << i+1 << " = ";
        fout << "D" << i+1 << ": center = a[" << i+1 << "][" << i+1 << "] = "
             << center << ",  radius r" << i+1 << " = ";

        bool first = true;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (!first) { cout << " + "; fout << " + "; }
            cout << "|" << mat[i][j] << "|";
            fout << "|" << mat[i][j] << "|";
            first = false;
        }
        cout << " = " << radius << "\n";
        fout << " = " << radius << "\n";

        cout << "    => D" << i+1 << " = (" << center << " - " << radius
             << ", " << center << " + " << radius << ") = ["
             << lo << ", " << hi << "]\n\n";
        fout << "    => D" << i+1 << " = (" << center << " - " << radius
             << ", " << center << " + " << radius << ") = ["
             << lo << ", " << hi << "]\n\n";
    }

    // Theorem statements
    fout << "--- Theorem ---\n";
    fout << "1) Every disk contains at least one eigenvalue.\n";
    fout << "2) Each eigenvalue is located in one of the disks.\n\n";

    fout << "--- Overall Eigenvalue Bounds ---\n";
    fout << "All eigenvalues lie in: ["
         << bounds.first << ", " << bounds.second << "]\n";
    fout << "=================================================\n";
}