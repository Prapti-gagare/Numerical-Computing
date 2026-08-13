#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "matrix.hpp"
#include <vector>
#include <fstream>
#include <string>

using namespace std;
class Interpolation : public Matrix
{
public:
    Interpolation();
    Interpolation(const Matrix &m);
    void loadDataPoints(ifstream &fin);
    void printDataPoints(ofstream &fout) const;
    virtual double interpolate(double xQuery, ofstream &fout) = 0;
    int    getN()const 
    { 
        return rows; 
    }      
    double getX(int i) const
    { 
        return mat[i][0]; 
    }
    double getY(int i) const 
    {
        return mat[i][1];
        
        }

protected:
    void validateDataPoints() const;
};

#endif