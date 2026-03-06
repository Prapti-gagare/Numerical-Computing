#include "matrix.hpp"
#include <stdexcept>

using namespace std;

Matrix::Matrix()
{
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        throw invalid_argument("Matrix size must be positive.");

    this->rows = rows;
    this->cols = cols;

    mat.resize(rows, vector<double>(cols, 0));
}

Matrix::Matrix(const Matrix &m)
{
    rows = m.rows;
    cols = m.cols;
    mat = m.mat;
}

void Matrix::readFromFile(ifstream &fin)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> mat[i][j];
}

void Matrix::displayToFile(ofstream &fout) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            fout << mat[i][j] << " ";
        fout << endl;
    }
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if (rows != m.rows || cols != m.cols)
        throw logic_error("Matrix addition not possible");

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] + m.mat[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix &m) const
{
    if (rows != m.rows || cols != m.cols)
        throw logic_error("Matrix subtraction not possible");

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] - m.mat[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (cols != m.rows)
        throw logic_error("Matrix multiplication not possible");

    Matrix result(rows, m.cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
        }
    }

    return result;
}
double &Matrix::operator()(int i, int j)
{
    return mat[i][j];
}

double Matrix::operator()(int i, int j) const
{
    return mat[i][j];
}

istream &operator>>(istream &in, Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            in >> m.mat[i][j];

    return in;
}

ostream &operator<<(ostream &out, const Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
            out << m.mat[i][j] << " ";
        out << endl;
    }

    return out;
}