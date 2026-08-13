import numpy as np
from matrixpy.interpolate import lagrange_interpolate, lagrange_basis


def test_lagrange_basis():
    x_points = np.array([1.0, 2.0, 3.0])
    # Test that L_i(x_i) = 1
    assert np.isclose(lagrange_basis(x_points, 0, 1.0), 1.0)
    assert np.isclose(lagrange_basis(x_points, 1, 2.0), 1.0)
    # Test that L_i(x_j) = 0 for i != j
    assert np.isclose(lagrange_basis(x_points, 0, 2.0), 0.0)


def test_lagrange_interpolate():
    x = np.array([1.0, 2.0, 3.0])
    y = np.array([1.0, 4.0, 9.0])  # y = x^2
    # Interpolate at x=2 should give 4
    result = lagrange_interpolate(x, y, 2.0)
    assert np.isclose(result, 4.0)
