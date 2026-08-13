"""Eigenvalue computations and helpers."""
import numpy as np
from scipy.linalg import eig as scipy_eig


def eig(A):
    """Compute eigenvalues and eigenvectors using scipy.

    Returns (eigenvalues, eigenvectors)
    """
    A = np.asarray(A, dtype=float)
    evals, evecs = scipy_eig(A)
    return evals, evecs


def gerschgorin_disks(A):
    """Compute Gerschgorin disks for matrix A.

    Each disk is centered at A[i,i] with radius = sum(|A[i,j]| for j != i).
    Returns list of (center, radius) tuples.
    """
    A = np.asarray(A, dtype=float)
    n = A.shape[0]
    disks = []
    for i in range(n):
        center = A[i, i]
        radius = np.sum(np.abs(A[i, :i])) + np.sum(np.abs(A[i, i + 1 :]))
        disks.append((center, radius))
    return disks


def gerschgorin_bounds(A):
    """Return global bounds (min_real, max_real, min_imag, max_imag) for Gerschgorin disks."""
    A = np.asarray(A, dtype=float)
    disks = gerschgorin_disks(A)
    min_real = min(c.real - r for c, r in disks)
    max_real = max(c.real + r for c, r in disks)
    min_imag = min(-r for _, r in disks)
    max_imag = max(r for _, r in disks)
    return (min_real, max_real, min_imag, max_imag)
