"""Decomposition routines for matrixpy.

These are lightweight, tested wrappers using numpy/scipy where appropriate.
"""
import numpy as np
from scipy.linalg import lu as scipy_lu


def lu_decompose(A):
    """Return (L, U, P) decomposition for A.

    P is the permutation matrix such that P @ A = L @ U
    """
    A = np.asarray(A, dtype=float)
    P, L, U = scipy_lu(A)
    return L, U, P


def cholesky(A):
    """Return lower-triangular Cholesky factor L for A (A = L @ L.T)."""
    A = np.asarray(A, dtype=float)
    return np.linalg.cholesky(A)
