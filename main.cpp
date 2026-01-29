#include <iostream>
#include "complex.hpp"
using namespace std;

int main()
 {
    complex c1, c2;
    cout << "enter real and imaginary part of c1: ";
    cin >> c1.real >> c1.imag;
    cout << "enter real and imaginary part of c2: ";
    cin >> c2.real >> c2.imag;
    complex c3 = c1.add(c2);
    complex c4 = c1.subtract(c2);
    complex c5 = c1.multiply(c2);
    complex c6 = c1.divide(c2);
    complex c7 = c1.conjugate();
    float m  = c1.norm();
   // cout << "\nc1 + c2 = " << c3.real << " + " << c3.imag << "i";
    cout<<"Complex number subtraction";
    c4.display();
    cout<<"\nComplex number addition";
    c3.display();
    cout << "\nc1 * c2 = " << c5.real << " + " << c5.imag << "i";
    cout << "\nc1 / c2 = " << c6.real << " + " << c6.imag << "i";
    cout << "\nConjugate of c1 = " << c7.real << " + " << c7.imag << "i";
    cout << "\nNorm of c1= " << m << endl;
    return 0;
}
