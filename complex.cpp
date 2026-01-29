#include "complex.hpp"
#include<iostream>

complex::complex()
{

}
complex::complex(float r, float i) 
{
    real = r;
    imag = i;
}
complex complex::add(complex c) 
{
    return complex(real+c.real,imag+c.imag);
}
complex complex::subtract(complex c)
 {
    return complex(real-c.real,imag-c.imag);
}
complex complex::multiply(complex c) 
{
    return complex(real*c.real-imag*c.imag,real*c.imag+imag*c.real);
}
complex complex::divide(complex c) 
{
    float denom = c.real*c.real+c.imag*c.imag;
    return complex((real*c.real+imag*c.imag)/denom,(imag*c.real-real*c.imag)/denom);
}
complex complex::conjugate() 
{
    return complex(real,-imag);
}
float complex::norm()
 {
    return real*real+imag*imag;
}
 void complex::display()
{
 if(imag>=0)
 std::cout << "\nc1 and c2 = " << real << " + " << imag << "i";
 else
 std::cout << "\nc1 and c2 = " << real << " + " << -imag << "i";

}

