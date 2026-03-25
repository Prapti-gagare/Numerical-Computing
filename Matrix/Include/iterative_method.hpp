#ifndef ITERATIVE_METHOD_HPP
#define ITERATIVE_METHOD_HPP

#include "LinearSystem.hpp"
#include <vector>
#include <fstream>

using namespace std;

class IterativeMethod : public LinearSystem
{
protected:
    int maxIterations;
    double tolerance;

public:
    IterativeMethod(const Matrix &m, int maxIter = 1000, double tol = 1e-6);

    virtual void solve(ofstream &fout) = 0;

    vector<double> extractB() const;   // RHS
    vector<vector<double>> extractA() const; // Coefficient matrix

    void printSolution(ofstream &fout, const vector<double> &x);
};

#endif