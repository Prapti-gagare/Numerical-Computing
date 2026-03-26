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
    void writeToFile(ofstream &fout) const;

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;
    bool   operator==(const Matrix &m) const;

    // Correct signatures: free-function friends so  cout << A  works
    friend ostream& operator<<(ostream &out, const Matrix &m);
    friend istream& operator>>(istream &in,        Matrix &m);

    bool isSquare()             const;
    bool isNull()               const;
    bool isIdentity()           const;
    bool isSymmetric()          const;
    bool isDiagonal()           const;
    bool isDiagonallyDominant() const;

    // Returns a diagonally-dominant copy.
    // Strategy: first try row permutation (partial pivoting).
    // If permutation alone is insufficient, apply a diagonal shift
    // (|a_ii| = sum_offdiag + epsilon) so iterative methods converge.
    Matrix makeDiagonallyDominant() const;

    Matrix transpose()  const;
    double determinant() const;
    Matrix adjoint()    const;
    Matrix inverse()    const;

private:
    void getCofactor(Matrix &temp, int p, int q, int n) const;
};

#endif