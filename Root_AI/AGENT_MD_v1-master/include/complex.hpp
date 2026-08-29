#ifndef COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP
#define COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP
class complex {
public:
    float real;   ///< Real part of the complex number
    float imag;   ///< Imaginary part of the complex number

    /**
     * @brief Default constructor.
     * Initializes a complex number to 0 + 0i.
     */
    complex();

    /**
     * @brief Parameterized constructor.
     * Initializes a complex number with the given real and imaginary parts.
     * 
     * @param r The real part
     * @param i The imaginary part
     */
    complex(float r, float i);
};

complex add(const complex& a, const complex& b);

complex subtract(const complex& a, const complex& b);

complex multiply(const complex& a, const complex& b);
complex divide(const complex& a, const complex& b);

complex conjugate(const complex& a);
float norm(const complex& a);


void display(const complex& a);

#endif 
