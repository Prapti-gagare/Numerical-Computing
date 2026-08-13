"""Small example demonstrating all matrixpy modules."""
import numpy as np
from matrixpy import lu_decompose, cholesky, gaussian_elimination
from matrixpy.eigen import eig, gerschgorin_disks
from matrixpy.interpolate import lagrange_interpolate
from matrixpy.fit import fit_polynomial, eval_polynomial


def main():
    print("=== matrixpy Examples ===\n")

    # 1. Decomposition
    print("1. LU Decomposition:")
    A = np.array([[3.0, 1.0], [1.0, 2.0]])
    L, U, P = lu_decompose(A)
    print(f"  A = \n{A}")
    print(f"  L @ U = \n{L @ U}")

    # 2. Solving
    print("\n2. Gaussian Elimination:")
    b = np.array([9.0, 8.0])
    x, resid = gaussian_elimination(A, b)
    print(f"  Solution: {x}")
    print(f"  Residual: {resid}")

    # 3. Eigenvalues
    print("\n3. Eigenvalues:")
    evals, evecs = eig(A)
    print(f"  Eigenvalues: {evals}")

    # 4. Gerschgorin
    print("\n4. Gerschgorin Disks:")
    disks = gerschgorin_disks(A)
    for i, (c, r) in enumerate(disks):
        print(f"  Disk {i}: center={c:.2f}, radius={r:.2f}")

    # 5. Interpolation
    print("\n5. Lagrange Interpolation:")
    x_pts = np.array([1.0, 2.0, 3.0])
    y_pts = np.array([1.0, 4.0, 9.0])
    y_interp = lagrange_interpolate(x_pts, y_pts, 1.5)
    print(f"  y(1.5) ≈ {y_interp:.2f} (actual x^2 = 2.25)")

    # 6. Curve Fitting
    print("\n6. Polynomial Fitting:")
    coeffs = fit_polynomial(x_pts, y_pts, degree=2)
    print(f"  Coefficients: {coeffs}")
    print(f"  y(1.5) = {eval_polynomial(coeffs, 1.5):.2f}")


if __name__ == "__main__":
    main()
