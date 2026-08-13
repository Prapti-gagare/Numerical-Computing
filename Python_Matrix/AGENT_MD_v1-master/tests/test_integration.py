"""Integration tests validating matrixpy against reference outputs."""
import numpy as np
from matrixpy import (
    lu_decompose, cholesky, gaussian_elimination,
    gauss_jacobi, gauss_seidel, eig,
    gerschgorin_disks, lagrange_interpolate, fit_polynomial
)


def test_integration_solve_system():
    """Test solving a larger system."""
    A = np.array([
        [4.0, 3.0, 0.0],
        [3.0, 4.0, -1.0],
        [0.0, -1.0, 4.0]
    ])
    b = np.array([24.0, 30.0, -24.0])
    x, resid = gaussian_elimination(A, b)
    assert np.allclose(A @ x, b, atol=1e-10)
    assert resid < 1e-10


def test_integration_iterative_convergence():
    """Test iterative solvers on diagonally dominant system."""
    A = np.array([
        [10.0, 1.0, 1.0],
        [1.0, 10.0, 1.0],
        [1.0, 1.0, 10.0]
    ])
    b = np.array([12.0, 12.0, 12.0])
    xj, itj = gauss_jacobi(A, b, tol=1e-10, maxiter=1000)
    xs, its = gauss_seidel(A, b, tol=1e-10, maxiter=1000)
    # Both should converge to approximately [1, 1, 1]
    assert np.allclose(xj, [1.0, 1.0, 1.0], atol=1e-6)
    assert np.allclose(xs, [1.0, 1.0, 1.0], atol=1e-6)
    # Gauss-Seidel typically converges faster
    assert its <= itj


def test_integration_eigenvalues_symmetry():
    """Test eigenvalues of symmetric matrix are real."""
    A = np.array([
        [2.0, 1.0],
        [1.0, 2.0]
    ])
    evals, evecs = eig(A)
    assert np.allclose(evals.imag, 0.0)  # All real


def test_integration_interpolation_and_fit():
    """Test that fitted polynomial passes through data points."""
    x = np.array([0.0, 1.0, 2.0, 3.0])
    y = np.array([1.0, 3.0, 7.0, 13.0])  # y = 1 + x + x^2
    
    # Fit quadratic
    coeffs = fit_polynomial(x, y, degree=2)
    
    # Interpolate at known points
    for xi, yi in zip(x, y):
        y_interp = lagrange_interpolate(x, y, xi)
        assert np.isclose(y_interp, yi, atol=1e-10)


def test_integration_cholesky_positive_definite():
    """Test Cholesky on positive definite matrix."""
    A = np.array([
        [4.0, 2.0],
        [2.0, 3.0]
    ])
    L = cholesky(A)
    assert np.allclose(L @ L.T, A)
    # L should be lower triangular
    assert np.allclose(L, np.tril(L))


def test_integration_lu_reconstruction():
    """Test LU factorization reconstructs original matrix."""
    A = np.array([
        [1.0, 2.0, 3.0],
        [2.0, 4.0, 5.0],
        [3.0, 5.0, 6.0]
    ])
    L, U, P = lu_decompose(A)
    A_reconstructed = P @ L @ U
    assert np.allclose(A_reconstructed, A)


def test_gerschgorin_contains_eigenvalues():
    """Test that eigenvalues lie within Gerschgorin disks."""
    A = np.array([
        [5.0, 0.5, 0.2],
        [0.5, 4.0, 0.1],
        [0.2, 0.1, 3.0]
    ])
    evals, _ = eig(A)
    disks = gerschgorin_disks(A)
    
    # Each eigenvalue should lie in at least one disk
    for eval_val in evals:
        in_disk = False
        for center, radius in disks:
            if abs(eval_val - center) <= radius + 1e-10:
                in_disk = True
                break
        assert in_disk, f"Eigenvalue {eval_val} not in any Gerschgorin disk"
