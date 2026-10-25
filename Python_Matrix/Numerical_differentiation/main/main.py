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
from src.simpsons1_3 import Simpson13Rule
from src.simpsons_3_8 import Simpson38Rule
from src.power_method import PowerMethod
from src.jacobi_method import JacobiMethod

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

def exp_antiderivative(x):
    return math.exp(x)

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
    a = float(input("Lower limit a [default 0]: ") or 0)
    b = float(input("Upper limit b [default 1]: ") or 1)

    f = TestFunction("e^x", exp_function, None, exp_antiderivative)
    exact_value = f.exact_integral(a, b)

    methods = [
        (TrapezoidalRule(), [1, 2, 4, 8, 16]),
        (Simpson13Rule(), [128,256,384,512,640]),
        (Simpson38Rule(), [3, 6, 9, 12, 15, 18])
    ]

    print(f"\nIntegral of {f.get_name()} from {a} to {b}")
    print(f"Exact value = {exact_value:.10f}")

    with open("integration_results.csv", "w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(["Function", "Method", "n", "h", "Approximation", "Exact", "Error"])

        for method, n_values in methods:
            print(f"\nMethod: {method.get_name()}")
            print(f"{'n':>4}{'h':>12}{'Approximation':>20}{'Absolute Error':>20}")

            for n in n_values:
                try:
                    h = method.step_size(a, b, n)
                    approx = method.integrate(f, a, b, n)
                    error = abs(exact_value - approx)
                    print(f"{n:>4}{h:>12.6f}{approx:>20.10f}{error:>20.10e}")
                    writer.writerow([f.get_name(), method.get_name(), n, h, approx, exact_value, error])
                except ValueError:
                    continue

    print("\nResults have been saved to integration_results.csv")


def find_input_file(filename):
    """Look for an input file in the current folder, next to main.py, then the project root."""
    for folder in (os.getcwd(), _this_dir, os.path.dirname(_this_dir)):
        path = os.path.join(folder, filename)
        if os.path.isfile(path):
            return path
    raise FileNotFoundError(f"Could not find {filename}")


def run_eigen():
    file_A = input("Matrix file [default inputA.txt]: ").strip() or "inputA.txt"
    tol = float(input("Tolerance [default 1e-8]: ") or 1e-8)

    solver = PowerMethod(max_iterations=max_it, tolerance=tol)
    solver.load_matrix(find_input_file(file_A))

    print(f"\nA : {solver.rows} x {solver.cols}")

    eigenvalue, eigenvector = solver.run()

    print("\n" + "=" * 50)
    print("Power Method - dominant eigenpair of A")
    print("=" * 50)
    print(f"Converged  : {solver.converged}")
    print(f"Iterations : {solver.iterations}")
    print(f"Eigenvalue : {eigenvalue:.10f}")
    print(f"Residual ||Av - lambda v|| : {solver.residual:.3e}")
    print("Eigenvector (unit norm), first 10 components:")
    for i, x in enumerate(eigenvector[:10], start=1):
        print(f"  v[{i:>2}] = {x: .10f}")
    if len(eigenvector) > 10:
        print(f"  ... ({len(eigenvector) - 10} more in the results file)")

    show_raw = input("\nShow the unscaled iteration vectors v_k = A*v_(k-1)? [y/N]: ").strip().lower()
    if show_raw == "y":
        raw = solver.get_raw_vectors()
        shown = raw if len(raw) <= 12 else raw[:6] + [None] + raw[-5:]
        print("\nUnscaled vectors (first 10 components of each):")
        for item in shown:
            if item is None:
                print("   ...")
                continue
            k = raw.index(item)
            print(f"  k={k:<3} (" + ", ".join(f"{x:.10g}" for x in item[:10]) + ")")
        solver.save_iterations_to_file("power_method_iterations.txt")
        print("Full unscaled vectors saved to power_method_iterations.txt")

    out = "power_method_results.txt"
    solver.save_results_to_file(out, eigenvalue, eigenvector)
    print(f"\nResults have been saved to {out}")


def run_jacobi():
    file_A = input("Matrix file [default inputA.txt]: ").strip() or "inputA.txt"
    tol = float(input("Tolerance [default 1e-8]: ") or 1e-8)
    solver = JacobiMethod(tolerance=tol)
    solver.load_matrix(find_input_file(file_A))
    eigenvalues, eigenvectors = solver.run()
    print("\nJacobi Rotation Method")
    print("Converged:", solver.converged)
    print("Iterations:", solver.iterations)
    print("Eigenvalues:")
    for i, value in enumerate(eigenvalues, 1):
        print(f"  lambda[{i}] = {value:.10f}")
    print("Eigenvectors (one vector per row):")
    for i, vector in enumerate(eigenvectors, 1):
        print(f"  v[{i}] = {vector}")
    out = "jacobi_method_results.txt"
    with open(out, "w") as f:
        f.write(f"Converged: {solver.converged}\nIterations: {solver.iterations}\n")
        for i, (value, vector) in enumerate(zip(eigenvalues, eigenvectors), 1):
            f.write(f"lambda[{i}] = {value:.12g}\nv[{i}] = {vector}\n")
    print(f"Results saved to {out}")


def main():
    print("1) Numerical differentiation")
    print("2) Numerical integration")
    print("3) Both")
    print("4) Eigenvalue & eigenvector (Power method)")
    print("5) Eigenvalues & eigenvectors (Jacobi rotation)")
    choice = input("Choose an option [1/2/3/4/5]: ").strip()

    if choice in ("1", "3"):
        run_differentiation()
    if choice in ("2", "3"):
        run_integration()
    if choice == "4":
        run_eigen()
    if choice == "5":
        run_jacobi()
    if choice not in ("1", "2", "3", "4", "5"):
        print("Invalid choice.")


if __name__ == "__main__":
    main()