"""Small example demonstrating solve and decomposition usage."""
import numpy as np
from matrixpy import gaussian_elimination, lu_decompose


def main():
    A = np.array([[3.0, 1.0], [1.0, 2.0]])
    b = np.array([9.0, 8.0])
    x, resid = gaussian_elimination(A, b)
    print("Solution:", x)
    print("Residual norm:", resid)
    L, U, P = lu_decompose(A)
    print("Reconstructed A (P A):\n", P.dot(A))
    print("L @ U:\n", L.dot(U))


if __name__ == "__main__":
    main()
