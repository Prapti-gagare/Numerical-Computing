import numpy as np
from matrixpy import gaussian_elimination, gauss_jacobi, gauss_seidel


def test_gaussian_elimination():
    A = np.array([[3.0, 1.0], [1.0, 2.0]])
    b = np.array([9.0, 8.0])
    x, resid = gaussian_elimination(A, b)
    assert np.allclose(A.dot(x), b)


def test_iterative_solvers():
    A = np.array([[5.0, 1.0], [2.0, 4.0]])
    b = np.array([12.0, 20.0])
    xj, itj = gauss_jacobi(A, b, tol=1e-10, maxiter=1000)
    xs, its = gauss_seidel(A, b, tol=1e-10, maxiter=1000)
    assert np.allclose(A.dot(xj), b, atol=1e-6)
    assert np.allclose(A.dot(xs), b, atol=1e-6)
