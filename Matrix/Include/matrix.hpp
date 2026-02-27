#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <cmath>

using namespace std;

class Matrix
{
public:
    int rows, cols;
    vector<vector<double>> mat;

    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix &m);

    void readFromFile(ifstream &fin);
    void displayToFile(ofstream &fout) const;

    Matrix add(const Matrix &m) const;
    Matrix subtract(const Matrix &m) const;

    void gaussianEliminationWithPivoting(ofstream &fout);
    void generateAugmentedMatrixFile(const string &leftFile, const string &rightFile,const string &outputFile);
};

class LinearSystem
{
public:
    Matrix A;
    LinearSystem(const Matrix &mat);
    virtual void solve(ofstream &fout) = 0;
};

class GaussianElimination : public LinearSystem
{
public:
    GaussianElimination(const Matrix &mat);
    void solve(ofstream &fout);
};

#endif