#include "Eigenvalue.hpp"
#include <stdexcept>

using namespace std;

EigenValue::EigenValue() : Matrix() {}

EigenValue::EigenValue(const Matrix &m) : Matrix(m) {}

void EigenValue::assertSquare() const
{
    if (rows != cols)
        throw logic_error("Eigenvalue computation requires a square matrix.");
}