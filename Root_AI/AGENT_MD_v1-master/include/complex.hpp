#ifndef COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP
#define COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP

/**
 * @file complex.hpp
 * @brief Declaration of the complex number class and operations.
 * 
 * This header defines a simple complex number class with support for
 * basic arithmetic operations (add, subtract, multiply, divide) and
 * utility operations (conjugate, norm, display).
 */

// ============================================================================
// Complex Number Class
// ============================================================================

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

/**
 * @brief Divide two complex numbers.
 * @param a First complex number (numerator)
 * @param b Second complex number (denominator)
 * @return The quotient (a / b); handles division by zero gracefully
 */
complex divide(const complex& a, const complex& b);

// ============================================================================
// Utility Operations
// ============================================================================

/**
 * @brief Compute the conjugate of a complex number.
 * @param a A complex number
 * @return The conjugate (real - imag*i)
 */
complex conjugate(const complex& a);

/**
 * @brief Compute the norm (magnitude) of a complex number.
 * @param a A complex number
 * @return The norm |a| = sqrt(real^2 + imag^2)
 */
float norm(const complex& a);

/**
 * @brief Display a complex number in human-readable format.
 * Prints to standard output in the format "real ± imag*i".
 * 
 * @param a A complex number
 */
void display(const complex& a);

#endif // COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP
