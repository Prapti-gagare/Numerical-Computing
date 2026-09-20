import math
import csv
import sys
import os

# Ensure both this script's folder and its parent are on the path,
# so 'src' is found whether it sits next to main.py or one level up
# (e.g. main.py inside a 'main' subfolder, src/ as a sibling of that).
_this_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _this_dir)
sys.path.insert(0, os.path.dirname(_this_dir))

from src.test_func import TestFunction
from src.forward_difference import ForwardDifference
from src.backward_difference import BackwardDifference
from src.central_difference import CentralDifference
from src.richardson import RichardsonExtrapolation
from src.lagrange import LagrangeInterpolation
from src.newton import NewtonInterpolation
from src.trapezoidal import TrapezoidalRule

def exp_function(x):
    return math.exp(x)

def exp_derivative(x):
    return math.exp(x)

def sin_function(x):
    return math.sin(x)

def sin_derivative(x):
    return math.cos(x)

def poly_function(x):
    return x**3 - 2 * x + 1

def poly_derivative(x):
    return 3 * x**2 - 2

def cos_function(x):
    return math.cos(x)

def cos_derivative(x):
    return -math.sin(x)

def square_function(x):
    return x ** 2

def square_antiderivative(x):
    return x ** 3 / 3

def run_method(f, method, x, exact_value, h_values, writer):
    print(f"\nMethod: {method.get_name()}")
    print(f"{'h':>12}{'Approximation':>20}{'Error':>20}")

    for h in h_values:
        approx = method.derivative(f, x, h)
        error = abs(exact_value - approx)
        print(f"{h:>12.6e}{approx:>20.6e}{error:>20.6e}")
        writer.writerow([
            f.get_name(),
            method.get_name(),
            h,
            approx,
            exact_value,
            error
        ])


def run_differentiation():
    x = 1.0
    n = int(input("Enter the number of step sizes (h values) to test: "))

    h_values = [
        float(input(f"Enter h[{i + 1}]: "))
        for i in range(n)
    ]

    functions = [
        TestFunction("exp(x)", exp_function, exp_derivative),
        TestFunction("sin(x)", sin_function, sin_derivative),
        TestFunction("x^3 - 2x + 1", poly_function, poly_derivative),
        TestFunction("cos(x)", cos_function, cos_derivative)
    ]

    methods = [
        ForwardDifference(),
        BackwardDifference(),
        CentralDifference(),
        RichardsonExtrapolation(),
        LagrangeInterpolation(),
        NewtonInterpolation()
    ]

    with open("results.csv", "w", newline="") as csv_file:

        writer = csv.writer(csv_file)

        writer.writerow([
            "Function",
            "Method",
            "h",
            "Approximation",
            "Exact",
            "Error"
        ])

        for f in functions:

            exact_value = f.exact(x)

            print("\n" + "=" * 50)
            print(f"Function: {f.get_name()}")
            print(f"Exact derivative at x=1: {exact_value:.6f}")
            print("=" * 50)

            for method in methods:
                run_method(
                    f,
                    method,
                    x,
                    exact_value,
                    h_values,
                    writer
                )

    print("\nResults have been saved to results.csv")


def run_integration():
    # Assignment: I = integral of x^2 dx  (limits default to 0 and 1)
    a = float(input("Lower limit a [default 0]: ") or 0)
    b = float(input("Upper limit b [default 1]: ") or 1)
    n_values = [1, 2, 4, 8, 16]

    f = TestFunction("x^2", square_function, None, square_antiderivative)
    method = TrapezoidalRule()
    exact_value = f.exact_integral(a, b)

    print(f"\nIntegral of {f.get_name()} from {a} to {b}")
    print(f"Exact value = {exact_value:.10f}")
    print(f"\nMethod: {method.get_name()}")
    print(f"{'n':>4}{'h':>12}{'Approximation':>20}{'Absolute Error':>20}")

    with open("trapezoidal_results.csv", "w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(["Function", "Method", "n", "h", "Approximation", "Exact", "Error"])

        for n in n_values:
            h = method.step_size(a, b, n)
            approx = method.integrate(f, a, b, n)
            error = abs(exact_value - approx)
            print(f"{n:>4}{h:>12.6f}{approx:>20.10f}{error:>20.10e}")
            writer.writerow([f.get_name(), method.get_name(), n, h, approx, exact_value, error])

    print("\nResults have been saved to trapezoidal_results.csv")


def main():
    print("1) Numerical differentiation")
    print("2) Trapezoidal rule integration")
    print("3) Both")
    choice = input("Choose an option [1/2/3]: ").strip()

    if choice in ("1", "3"):
        run_differentiation()
    if choice in ("2", "3"):
        run_integration()
    if choice not in ("1", "2", "3"):
        print("Invalid choice.")


if __name__ == "__main__":
    main()