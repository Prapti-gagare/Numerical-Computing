import numpy as np
from matrixpy.fit import fit_polynomial, eval_polynomial, rmse


def test_fit_polynomial():
    x = np.array([1.0, 2.0, 3.0])
    y = np.array([1.0, 4.0, 9.0])  # y = x^2
    coeffs = fit_polynomial(x, y, degree=2)
    # Should fit y = x^2, so coeffs ≈ [0, 0, 1]
    assert len(coeffs) == 3
    assert np.allclose(eval_polynomial(coeffs, x), y, atol=1e-5)


def test_eval_polynomial():
    coeffs = [1.0, 2.0, 3.0]  # 1 + 2*x + 3*x^2
    result = eval_polynomial(coeffs, 1.0)
    assert np.isclose(result, 1 + 2 + 3)  # = 6


def test_rmse():
    x = np.array([1.0, 2.0, 3.0])
    y = np.array([1.0, 4.0, 9.0])
    coeffs = [0.0, 0.0, 1.0]  # y = x^2
    error = rmse(x, y, coeffs)
    assert error < 1e-5
