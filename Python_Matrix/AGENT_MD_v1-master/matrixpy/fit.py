"""Curve fitting and least-squares helpers."""
import numpy as np


def fit_polynomial(x, y, degree):
    """Fit a polynomial of given degree to (x, y) data.

    Returns coefficients [a0, a1, ..., a_degree] where y = a0 + a1*x + ... + a_degree*x^degree
    """
    x = np.asarray(x, dtype=float)
    y = np.asarray(y, dtype=float)
    coeffs = np.polyfit(x, y, degree)
    return coeffs[::-1]  # Reverse to get ascending powers


def eval_polynomial(coeffs, x):
    """Evaluate polynomial at x given coefficients [a0, a1, ...] (ascending powers)."""
    x = np.asarray(x, dtype=float)
    result = 0.0
    for power, coeff in enumerate(coeffs):
        result += coeff * (x ** power)
    return result


def rmse(x, y, coeffs):
    """Compute root mean squared error for fitted polynomial."""
    y_pred = eval_polynomial(coeffs, x)
    return np.sqrt(np.mean((y - y_pred) ** 2))
