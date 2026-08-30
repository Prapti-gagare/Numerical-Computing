import math
import csv

from test_func import TestFunction
from forward_difference import ForwardDifference
from backward_difference import BackwardDifference
from central_difference import CentralDifference
from richardson import RichardsonExtrapolation


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


def main():

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
        RichardsonExtrapolation()
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


if __name__ == "__main__":
    main()