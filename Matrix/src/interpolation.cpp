#include "interpolation.hpp"
#include <stdexcept>
#include <iomanip>

using namespace std;
Interpolation::Interpolation() : Matrix() {}

Interpolation::Interpolation(const Matrix &m) : Matrix(m)
{
    validateDataPoints();
}
void Interpolation::loadDataPoints(ifstream &fin)
{
    if (!fin)
        throw runtime_error("Interpolation: file stream is not open.");

    int n;
    if (!(fin >> n) || n <= 0)
        throw runtime_error("Interpolation: invalid or missing data-point count in file.");
    rows = n;
    cols = 2;
    mat.assign(rows, vector<double>(cols, 0.0));

    for (int i = 0; i < n; i++)
    {
        if (!(fin >> mat[i][0] >> mat[i][1]))
            throw runtime_error("Interpolation: unexpected end of file at row " + to_string(i));
    }
}


void Interpolation::printDataPoints(ofstream &fout) const
{
    validateDataPoints();
    fout << fixed << setprecision(6);

    fout << "\nData Points:\n";
    for (int i = 0; i < rows; i++)
    {
        fout << "Point " << i 
             << " : x = " << mat[i][0] 
             << ", f(x) = " << mat[i][1] << "\n";
    }
    fout << "\n";
}

void Interpolation::validateDataPoints() const
{
    if (cols != 2)
        throw logic_error("Interpolation: data matrix must have exactly 2 columns (x and y).");
    if (rows < 2)
        throw logic_error("Interpolation: at least 2 data points are required.");
}