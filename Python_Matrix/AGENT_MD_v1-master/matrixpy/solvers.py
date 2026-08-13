"""Linear system solvers: direct and iterative implementations."""
import numpy as np


def gaussian_elimination(A, b):
    """Solve Ax = b using a direct solver (numpy.linalg.solve).

    Returns (x, residual_norm)
    """
    A = np.asarray(A, dtype=float)
    b = np.asarray(b, dtype=float)
    x = np.linalg.solve(A, b)
    residual = np.linalg.norm(A.dot(x) - b)
    return x, residual


def gauss_jacobi(A, b, tol=1e-8, maxiter=10000):
    A = np.asarray(A, dtype=float)
    b = np.asarray(b, dtype=float)
    n = A.shape[0]
    x = np.zeros_like(b, dtype=float)
    D = np.diag(A)
    R = A - np.diagflat(D)
    for i in range(maxiter):
        x_new = (b - R.dot(x)) / D
        if np.linalg.norm(x_new - x) < tol:
            return x_new, i + 1
        x = x_new
    return x, maxiter


def gauss_seidel(A, b, tol=1e-8, maxiter=10000):
    A = np.asarray(A, dtype=float)
    b = np.asarray(b, dtype=float)
    n = A.shape[0]
    x = np.zeros_like(b, dtype=float)
    for k in range(maxiter):
        x_new = x.copy()
        for i in range(n):
            s1 = A[i, :i].dot(x_new[:i])
            s2 = A[i, i + 1 :].dot(x[i + 1 :])
            x_new[i] = (b[i] - s1 - s2) / A[i, i]
        if np.linalg.norm(x_new - x) < tol:
            return x_new, k + 1
        x = x_new
    return x, maxiter
