#include "matrix.hpp"
#include <stdexcept>
#include <cmath>

using namespace std;

Matrix::Matrix()
{
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int r, int c)
{
    if(r <= 0 || c <= 0)
        throw invalid_argument("Matrix size must be positive");

    rows = r;
    cols = c;

    mat.resize(rows, vector<double>(cols,0));
}

Matrix::Matrix(const Matrix &m)
{
    rows = m.rows;
    cols = m.cols;
    mat = m.mat;
}

void Matrix::readFromFile(ifstream &fin)
{
    if(!fin)
        throw runtime_error("File not opened");

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(!(fin >> mat[i][j]))
                throw runtime_error("Invalid matrix data in file");
}

void Matrix::writeToFile(ofstream &fout) const
{
    if(!fout)
        throw runtime_error("File not opened");

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            fout << mat[i][j] << " ";
        fout << endl;
    }
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if(rows != m.rows || cols != m.cols)
        throw invalid_argument("Addition not possible: matrix sizes must match");

    Matrix result(rows,cols);

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.mat[i][j] = mat[i][j] + m.mat[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix &m) const
{
    if(rows != m.rows || cols != m.cols)
        throw invalid_argument("Subtraction not possible: matrix sizes must match");

    Matrix result(rows,cols);

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.mat[i][j] = mat[i][j] - m.mat[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if(cols != m.rows)
        throw invalid_argument("Multiplication not possible: incompatible dimensions");

    Matrix result(rows,m.cols);

    for(int i=0;i<rows;i++)
        for(int j=0;j<m.cols;j++)
            for(int k=0;k<cols;k++)
                result.mat[i][j] += mat[i][k] * m.mat[k][j];

    return result;
}

double Matrix::get(int i,int j) const
{
    if(i<0 || i>=rows || j<0 || j>=cols)
        throw out_of_range("Matrix index out of range");

    return mat[i][j];
}

void Matrix::set(int i,int j,double value)
{
    if(i<0 || i>=rows || j<0 || j>=cols)
        throw out_of_range("Matrix index out of range");

    mat[i][j] = value;
}

istream& Matrix::operator>>(istream &in)
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            in >> mat[i][j];

    return in;
}
ostream& Matrix::operator<<(ostream &out) 
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            out << mat[i][j] << " ";

        out << endl;
    }

    return out;
}

/*void Matrix::output(ostream &out,const Matrix &m)
{
    for(int i=0;i<m.rows;i++)
    {
        for(int j=0;j<m.cols;j++)
            out << m.mat[i][j] << " ";
        out << endl;
    }

    return out;
}*/

bool Matrix::operator==(const Matrix &m) const
{
    if(rows != m.rows || cols != m.cols)
        return false;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(mat[i][j] != m.mat[i][j])
                return false;

    return true;
}

bool Matrix::isSquare() const
{
    return rows == cols;
}

bool Matrix::isNull() const
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(mat[i][j] != 0)
                return false;

    return true;
}

bool Matrix::isIdentity() const
{
    if(!isSquare())
        return false;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            if(i==j && mat[i][j] != 1)
                return false;

            if(i!=j && mat[i][j] != 0)
                return false;
        }

    return true;
}

bool Matrix::isSymmetric() const
{
    if(!isSquare())
        return false;

    for(int i=0;i<rows;i++)
        for(int j=i+1;j<cols;j++)
            if(mat[i][j] != mat[j][i])
                return false;

    return true;
}

bool Matrix::isDiagonal() const
{
    if(!isSquare())
        return false;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(i!=j && mat[i][j] != 0)
                return false;

    return true;
}

bool Matrix::isDiagonallyDominant() const
{
    if(!isSquare())
        return false;

    for(int i=0;i<rows;i++)
    {
        double sum = 0;

        for(int j=0;j<cols;j++)
        {
            if(i!=j)
                sum += abs(mat[i][j]);
        }

        if(abs(mat[i][i]) < sum)
            return false;
    }

    return true;
}

Matrix Matrix::makeDiagonallyDominant()
{
    if(!isSquare())
        throw logic_error("Diagonal dominance only defined for square matrices");

    Matrix result = *this;   

    for(int i=0;i<rows;i++)
    {
        int maxRow = i;
        double maxVal = abs(result.mat[i][i]);

        for(int k=i+1;k<rows;k++)
        {
            if(abs(result.mat[k][i]) > maxVal)
            {
                maxVal = abs(result.mat[k][i]);
                maxRow = k;
            }
        }

        if(maxRow != i)
            swap(result.mat[i], result.mat[maxRow]);
    }

    if(!result.isDiagonallyDominant())
        throw runtime_error("Matrix cannot be converted to diagonally dominant form");

    return result;
}

Matrix Matrix::transpose() const
{
    if(rows == 0 || cols == 0)
        throw logic_error("Transpose not possible for empty matrix");

    Matrix t(cols,rows);

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            t.mat[j][i] = mat[i][j];

    return t;
}

void Matrix::getCofactor(Matrix &temp,int p,int q,int n) const
{
    int i=0,j=0;

    for(int row=0;row<n;row++)
    {
        for(int col=0;col<n;col++)
        {
            if(row!=p && col!=q)
            {
                temp.mat[i][j++] = mat[row][col];

                if(j == n-1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double Matrix::determinant() const
{
    if(!isSquare())
        throw logic_error("Determinant not possible: matrix must be square");

    int n = rows;

    if(n == 1)
        return mat[0][0];

    if(n == 2)
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    double det = 0;
    int sign = 1;

    Matrix temp(n-1,n-1);

    for(int f=0; f<n; f++)
    {
        getCofactor(temp,0,f,n);
        det += sign * mat[0][f] * temp.determinant();
        sign = -sign;
    }

    return det;
}

Matrix Matrix::adjoint() const
{
    if(!isSquare())
        throw logic_error("Adjoint not possible: matrix must be square");

    int n = rows;
    Matrix adj(n,n);

    if(n == 1)
    {
        adj.mat[0][0] = 1;
        return adj;
    }

    int sign;
    Matrix temp(n-1,n-1);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            getCofactor(temp,i,j,n);

            sign = ((i+j)%2==0)?1:-1;

            adj.mat[j][i] = sign * temp.determinant();
        }
    }

    return adj;
}

Matrix Matrix::inverse() const
{
    if(!isSquare())
        throw logic_error("Inverse not possible: matrix must be square");

    double det = determinant();

    if(det == 0)
        throw logic_error("Inverse not possible: determinant is zero");

    int n = rows;

    Matrix adj = adjoint();
    Matrix inv(n,n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            inv.mat[i][j] = adj.mat[i][j] / det;

    return inv;
}