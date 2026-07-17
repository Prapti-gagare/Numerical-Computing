#include "complex.hpp"
#include <iostream>
#include <limits>

int main() {
    std::cout << "Enter the first complex number (real imag): ";
    float real1, imag1;
    if (!(std::cin >> real1 >> imag1)) {
        std::cerr << "Invalid input for the first complex number." << std::endl;
        return 1;
    }

    std::cout << "Enter the second complex number (real imag): ";
    float real2, imag2;
    if (!(std::cin >> real2 >> imag2)) {
        std::cerr << "Invalid input for the second complex number." << std::endl;
        return 1;
    }

    complex a(real1, imag1);
    complex b(real2, imag2);

    std::cout << "\nFirst complex number: ";
    display(a);
    std::cout << "Second complex number: ";
    display(b);
    std::cout << std::endl;

    complex sum = add(a, b);
    std::cout << "Sum: ";
    display(sum);

    complex difference = subtract(a, b);
    std::cout << "Difference: ";
    display(difference);

    complex product = multiply(a, b);
    std::cout << "Product: ";
    display(product);

    complex quotient = divide(a, b);
    std::cout << "Quotient: ";
    display(quotient);

    complex conjugated = conjugate(a);
    std::cout << "Conjugate of the first number: ";
    display(conjugated);

    std::cout << "Norm of the first number: " << norm(a) << std::endl;
    std::cout << "Norm of the second number: " << norm(b) << std::endl;

    return 0;
}
