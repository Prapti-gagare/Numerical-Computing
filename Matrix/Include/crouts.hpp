#ifndef CROUT_HPP
#define CROUT_HPP

#include "lu.hpp"

using namespace std;

class CroutLU : public LU
{
public:
    CroutLU(const Matrix &m);
    void solve(ofstream &fout);
};

#endif