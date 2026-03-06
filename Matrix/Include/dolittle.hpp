#ifndef DOLITTLE_HPP
#define DOLITTLE_HPP

#include "lu.hpp"

using namespace std;

class DolittleLU : public LU
{
public:
    DolittleLU(const Matrix &m);
    void solve(ofstream &fout);
};

#endif