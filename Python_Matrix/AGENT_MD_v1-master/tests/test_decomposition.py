import numpy as np
from matrixpy import lu_decompose, cholesky


def test_cholesky():
    A = np.array([[4.0, 2.0], [2.0, 3.0]])
    L = cholesky(A)
    assert np.allclose(L.dot(L.T), A)


def test_lu_decompose():
    A = np.array([[3.0, 1.0], [2.0, 4.0]])
    L, U, P = lu_decompose(A)
    assert np.allclose(P.dot(A), L.dot(U))
