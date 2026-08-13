"""Interpolation routines (Lagrange polynomial interpolation)."""
import numpy as np


def lagrange_basis(x_points, i, x):
    """Compute Lagrange basis polynomial L_i(x) for x_points and query x."""
    x_points = np.asarray(x_points, dtype=float)
    L = 1.0
    for j, xj in enumerate(x_points):
        if i != j:
            L *= (x - xj) / (x_points[i] - xj)
    return L


def lagrange_interpolate(x_points, y_points, x):
    """Interpolate using Lagrange polynomials.

    Given points (x_points, y_points), compute y(x) using Lagrange interpolation.
    """
    x_points = np.asarray(x_points, dtype=float)
    y_points = np.asarray(y_points, dtype=float)
    result = 0.0
    for i in range(len(x_points)):
        result += y_points[i] * lagrange_basis(x_points, i, x)
    return result
