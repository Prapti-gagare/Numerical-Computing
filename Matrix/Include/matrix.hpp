#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Matrix
{
protected:
    int rows, cols;
    vector<vector<double>> mat;

public:
    Matrix(); 
    Matrix(int rows, int cols);
    Matrix(const Matrix &m);

    void readFromFile(ifstream &fin);
    void displayToFile(ofstream &fout) const;

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;

    double &operator()(int i, int j);
    double operator()(int i, int j) const;

    friend istream &operator>>(istream &in, Matrix &m);
    friend ostream &operator<<(ostream &out, const Matrix &m);
};

#endif