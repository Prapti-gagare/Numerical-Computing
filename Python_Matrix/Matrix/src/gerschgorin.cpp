#include "gerschgorin.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
Gerschgorin::Gerschgorin(const Matrix &m) : EigenValue(m) {}
vector<pair<double, double>> Gerschgorin::computeDisks()
{
    Square();
    int n = rows;
    vector<pair<double, double>> disks(n); 

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

void Gerschgorin::printEigenvalues(ofstream &fout)
{
    Square();
    int n = rows;

    auto disks     = computeDisks();
    auto intervals = estimateEigenvalues();
    auto bounds    = globalBounds();
    fout << "Matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fout << mat[i][j] << " ";
        fout << "\n";
    }

    fout << fixed << setprecision(4);

    for (int i = 0; i < n; i++)
    {
        double center = disks[i].first;
        double radius = disks[i].second;
        double lo     = intervals[i].first;
        double hi     = intervals[i].second;
        fout << "D" << i+1 << ": center = a[" << i+1 << "][" << i+1 << "] = "
             << center << ",  radius r" << i+1 << " = ";

        bool first = true;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (!first) { cout << " + "; fout << " + "; }
            fout << "|" << mat[i][j] << "|";
            first = false;
        }
        fout << " = " << radius << "\n";
        fout << "    => D" << i+1 << " = (" << center << " - " << radius
             << ", " << center << " + " << radius << ") = ["
             << lo << ", " << hi << "]\n\n";
    }

    fout << "All eigenvalues lie in: ["
         << bounds.first << ", " << bounds.second << "]\n";
}