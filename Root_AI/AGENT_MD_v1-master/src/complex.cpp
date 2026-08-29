#include "complex.hpp"
#include <iostream>
#include <limits>
#include <cmath>

complex::complex() : real(0.0f), imag(0.0f) {}
complex::complex(float r, float i) : real(r), imag(i) {}

complex add(const complex& a, const complex& b) {
    return complex(a.real + b.real, a.imag + b.imag);
}

complex subtract(const complex& a, const complex& b) {
    return complex(a.real - b.real, a.imag - b.imag);
}

/**
 * @brief Multiply two complex numbers.
 * @param a First complex number
 * @param b Second complex number
 * @return The product (a * b)
 */
complex multiply(const complex& a, const complex& b) {
    float real_part = a.real * b.real - a.imag * b.imag;
    float imag_part = a.real * b.imag + a.imag * b.real;
    return complex(real_part, imag_part);
}

/**
 * @brief Divide two complex numbers.
 * @param a First complex number (numerator)
 * @param b Second complex number (denominator)
 * @return The quotient (a / b); handles division by zero gracefully
 */
complex divide(const complex& a, const complex& b) {
    // Check for division by zero
    if (b.real == 0.0f && b.imag == 0.0f) {
        std::cerr << "Error: Division by zero attempted." << std::endl;
        // Return a special value (NaN, NaN) to indicate error
        return complex(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
    }

    // Complex division: (a * conjugate(b)) / |b|^2
    complex conj_b = conjugate(b);
    float norm_b_sq = b.real * b.real + b.imag * b.imag;

    complex numerator = multiply(a, conj_b);
    return complex(numerator.real / norm_b_sq, numerator.imag / norm_b_sq);
}

// ============================================================================
// Utility Operations
// ============================================================================

/**
 * @brief Compute the conjugate of a complex number.
 * @param a A complex number
 * @return The conjugate (real - imag*i)
 */
complex conjugate(const complex& a) {
    return complex(a.real, -a.imag);
}

/**
 * @brief Compute the norm (magnitude) of a complex number.
 * @param a A complex number
 * @return The norm |a| = sqrt(real^2 + imag^2)
 */
float norm(const complex& a) {
    return std::sqrt(a.real * a.real + a.imag * a.imag);
}

/**
 * @brief Display a complex number in human-readable format.
 * Prints to standard output in the format "real ± imag*i".
 * 
 * @param a A complex number
 */
void display(const complex& a) {
    auto print_value = [](float value) {
        if (value == 0.0f) {
            std::cout << 0;
        } else {
            std::cout << value;
        }
    };

    print_value(a.real);
    if (a.imag < 0) {
        std::cout << " - ";
        print_value(-a.imag);
    } else {
        std::cout << " + ";
        print_value(a.imag);
    }
    std::cout << "i" << std::endl;
}