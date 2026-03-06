#ifndef LU_HPP
#define LU_HPP

#include "LinearSystem.hpp"
#include <vector>
#include <fstream>
using namespace std;
class LU : public LinearSystem
{
public:
    LU(const Matrix &m);
    vector<double> forwardSubstitution(vector<std::vector<double>> &L,vector<double> &b); 
    vector<double> backSubstitution(vector<std::vector<double>> &U,vector<double> &y);
    void printSolution(ofstream &fout,vector<double> &x);
};

#endif