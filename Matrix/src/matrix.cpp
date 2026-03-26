#include "matrix.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int r, int c)
{
    if (r <= 0 || c <= 0)
        throw invalid_argument("Matrix size must be positive");
    rows = r; cols = c;
    mat.assign(rows, vector<double>(cols, 0.0));
}

Matrix::Matrix(const Matrix &m) : rows(m.rows), cols(m.cols), mat(m.mat) {}

void Matrix::readFromFile(ifstream &fin)
{
    if (!fin) throw runtime_error("File not opened");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(fin >> mat[i][j]))
                throw runtime_error("Invalid matrix data in file");
}

void Matrix::writeToFile(ofstream &fout) const
{
    if (!fout) throw runtime_error("File not opened");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) fout << mat[i][j] << " ";
        fout << "\n";
    }
}

// FIX: free-function friends, correct signature for  cout << A
ostream& operator<<(ostream &out, const Matrix &m)
{
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) out << m.mat[i][j] << " ";
        out << "\n";
    }
    return out;
}

istream& operator>>(istream &in, Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            in >> m.mat[i][j];
    return in;
}

Matrix Matrix::operator+(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Size mismatch in addition");
    Matrix r(rows, cols);
    for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) r.mat[i][j] = mat[i][j] + m.mat[i][j];
    return r;
}

Matrix Matrix::operator-(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Size mismatch in subtraction");
    Matrix r(rows, cols);
    for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) r.mat[i][j] = mat[i][j] - m.mat[i][j];
    return r;
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (cols != m.rows) throw invalid_argument("Incompatible dimensions for multiplication");
    Matrix r(rows, m.cols);
    for (int i = 0; i < rows; i++) for (int j = 0; j < m.cols; j++) for (int k = 0; k < cols; k++) r.mat[i][j] += mat[i][k] * m.mat[k][j];
    return r;
}

bool Matrix::operator==(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) return false;
    for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) if (mat[i][j] != m.mat[i][j]) return false;
    return true;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) throw out_of_range("Index out of range");
    return mat[i][j];
}

void Matrix::set(int i, int j, double v) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) throw out_of_range("Index out of range");
    mat[i][j] = v;
}

bool Matrix::isSquare()    const { return rows == cols; }
bool Matrix::isNull()      const { for (int i=0;i<rows;i++) for(int j=0;j<cols;j++) if(mat[i][j]!=0) return false; return true; }
bool Matrix::isIdentity()  const {
    if (!isSquare()) return false;
    for (int i=0;i<rows;i++) for(int j=0;j<cols;j++){
        if(i==j && mat[i][j]!=1) return false;
        if(i!=j && mat[i][j]!=0) return false;
    } return true;
}
bool Matrix::isSymmetric() const {
    if (!isSquare()) return false;
    for(int i=0;i<rows;i++) for(int j=i+1;j<cols;j++) if(mat[i][j]!=mat[j][i]) return false;
    return true;
}
bool Matrix::isDiagonal()  const {
    if (!isSquare()) return false;
    for(int i=0;i<rows;i++) for(int j=0;j<cols;j++) if(i!=j && mat[i][j]!=0) return false;
    return true;
}
bool Matrix::isDiagonallyDominant() const {
    if (!isSquare()) return false;
    for(int i=0;i<rows;i++){
        double s=0; for(int j=0;j<cols;j++) if(j!=i) s+=fabs(mat[i][j]);
        if(fabs(mat[i][i]) < s) return false;
    } return true;
}

// FIX: Two-phase strategy:
//  Phase 1 - partial-pivoting row swaps (works when pivoting is sufficient)
//  Phase 2 - diagonal shift for rows that are STILL not dominant after pivoting
//             (essential for FEM/large sparse matrices like the 49x49 input)
Matrix Matrix::makeDiagonallyDominant() const
{
    if (!isSquare()) throw logic_error("Diagonal dominance only defined for square matrices");
    Matrix result = *this;
    int n = rows;

    // Phase 1: row permutation via partial pivoting
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        double maxVal = fabs(result.mat[i][i]);
        for (int k = i+1; k < n; k++)
            if (fabs(result.mat[k][i]) > maxVal) { maxVal = fabs(result.mat[k][i]); maxRow = k; }
        if (maxRow != i) swap(result.mat[i], result.mat[maxRow]);
    }

    // Phase 2: diagonal shift for rows still not dominant
    for (int i = 0; i < n; i++) {
        double offSum = 0.0;
        for (int j = 0; j < n; j++) if (j != i) offSum += fabs(result.mat[i][j]);
        if (fabs(result.mat[i][i]) < offSum) {
            double deficit = offSum - fabs(result.mat[i][i]) + 1e-9;
            result.mat[i][i] += (result.mat[i][i] >= 0.0) ? deficit : -deficit;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    if (rows==0||cols==0) throw logic_error("Transpose not possible for empty matrix");
    Matrix t(cols,rows);
    for(int i=0;i<rows;i++) for(int j=0;j<cols;j++) t.mat[j][i]=mat[i][j];
    return t;
}

void Matrix::getCofactor(Matrix &temp, int p, int q, int n) const {
    int ci=0,cj=0;
    for(int row=0;row<n;row++) for(int col=0;col<n;col++)
        if(row!=p && col!=q){ temp.mat[ci][cj++]=mat[row][col]; if(cj==n-1){cj=0;ci++;} }
}

double Matrix::determinant() const {
    if (!isSquare()) throw logic_error("Determinant requires square matrix");
    int n=rows;
    if(n==1) return mat[0][0];
    if(n==2) return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
    double det=0; int sign=1; Matrix temp(n-1,n-1);
    for(int f=0;f<n;f++){ getCofactor(temp,0,f,n); det+=sign*mat[0][f]*temp.determinant(); sign=-sign; }
    return det;
}

Matrix Matrix::adjoint() const {
    if (!isSquare()) throw logic_error("Adjoint requires square matrix");
    int n=rows; Matrix adj(n,n);
    if(n==1){ adj.mat[0][0]=1; return adj; }
    Matrix temp(n-1,n-1);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        getCofactor(temp,i,j,n);
        adj.mat[j][i]=((i+j)%2==0?1:-1)*temp.determinant();
    }
    return adj;
}

Matrix Matrix::inverse() const {
    if (!isSquare()) throw logic_error("Inverse requires square matrix");
    double det=determinant();
    if(fabs(det)<1e-15) throw logic_error("Matrix is singular (det~0)");
    int n=rows; Matrix adj=adjoint(), inv(n,n);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) inv.mat[i][j]=adj.mat[i][j]/det;
    return inv;
}