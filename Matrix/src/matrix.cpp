#include "matrix.hpp"

Matrix::Matrix() 
{ rows = cols = 0; 
}

Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) throw invalid_argument("Matrix size must be positive.");
    this->rows = rows;
    this->cols = cols;
    mat.resize(rows, vector<double>(cols, 0));
}

Matrix::Matrix(const Matrix &m) { rows = m.rows; cols = m.cols; mat = m.mat; }

void Matrix::readFromFile(ifstream &fin)
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            fin >> mat[i][j];
}

void Matrix::displayToFile(ofstream &fout) const
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            fout << mat[i][j] << " ";
        fout << endl;
    }
}

Matrix Matrix::add(const Matrix &m) const
{
    if(rows!=m.rows || cols!=m.cols) throw logic_error("Addition not possible");
    Matrix result(rows, cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.mat[i][j] = mat[i][j]+m.mat[i][j];
    return result;
}

Matrix Matrix::subtract(const Matrix &m) const
{
    if(rows!=m.rows || cols!=m.cols) throw logic_error("Subtraction not possible");
    Matrix result(rows, cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.mat[i][j] = mat[i][j]-m.mat[i][j];
    return result;
}

void Matrix::gaussianEliminationWithPivoting(ofstream &fout)
{
    if(cols != rows+1) throw logic_error("Matrix must be augmented (n x n+1)");

    for(int k=0;k<rows-1;k++)
    {
        int maxRow = k;
        for(int i=k+1;i<rows;i++)
            if(abs(mat[i][k]) > abs(mat[maxRow][k])) maxRow = i;
        if(mat[maxRow][k]==0) { fout << "No unique solution.\n"; return; }
        if(maxRow!=k) swap(mat[k], mat[maxRow]);
        for(int i=k+1;i<rows;i++)
        {
            double factor = mat[i][k]/mat[k][k];
            for(int j=k;j<cols;j++)
                mat[i][j] -= factor*mat[k][j];
        }
    }

    vector<double> x(rows);
    for(int i=rows-1;i>=0;i--)
    {
        if(mat[i][i]==0) throw runtime_error("No unique solution.");
        x[i] = mat[i][cols-1];
        for(int j=i+1;j<rows;j++)
            x[i] -= mat[i][j]*x[j];
        x[i] /= mat[i][i];
    }

    for(int i=0;i<rows;i++)
        fout << "x" << i+1 << " = " << x[i] << endl;
}

void Matrix::generateAugmentedMatrixFile(const string &leftFile, const string &rightFile,const string &outputFile)
{
    ifstream finL(leftFile);
    ifstream finR(rightFile);
    ofstream fout(outputFile);
    if(!finL || !finR || !fout) throw runtime_error("File opening error for augmented matrix.");

    int rL,cL,rR,cR;
    finL >> rL >> cL;
    finR >> rR >> cR;

    if(rL!=rR || cR!=1) throw runtime_error("Dimension mismatch for augmented matrix.");

    fout << rL << " " << (cL+1) << "\n";

    for(int i=0;i<rL;i++)
    {
        for(int j=0;j<cL;j++)
        {
            double val; finL >> val;
            fout << val << " ";
        }
        double rhs; finR >> rhs;
        fout << rhs << "\n";
    }

    finL.close(); finR.close(); fout.close();
    cout << "Augmented matrix saved to " << outputFile << endl;
}

LinearSystem::LinearSystem(const Matrix &mat) : A(mat) {
    
}

GaussianElimination::GaussianElimination(const Matrix &mat) : LinearSystem(mat) 
{

}
void GaussianElimination::solve(ofstream &fout)
 { 
    A.gaussianEliminationWithPivoting(fout); 
}