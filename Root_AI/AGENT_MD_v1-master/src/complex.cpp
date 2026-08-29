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

complex multiply(const complex& a, const complex& b) {
    float real_part = a.real * b.real - a.imag * b.imag;
    float imag_part = a.real * b.imag + a.imag * b.real;
    return complex(real_part, imag_part);
}

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

complex conjugate(const complex& a) {
    return complex(a.real, -a.imag);
}

float norm(const complex& a) {
    return std::sqrt(a.real * a.real + a.imag * a.imag);
}

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