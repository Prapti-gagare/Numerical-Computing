"""matrixpy -- lightweight Python port of Matrix/ C++ utilities.

Modules:
  - decomposition: LU, Cholesky decompositions
  - solvers: Gaussian elimination, Gauss-Jacobi, Gauss-Seidel
  - eigen: Eigenvalue computations and Gerschgorin disks
  - interpolate: Lagrange polynomial interpolation
  - fit: Polynomial curve fitting with RMSE
  - utils: I/O and matrix utilities
"""

from .decomposition import lu_decompose, cholesky
from .solvers import gaussian_elimination, gauss_jacobi, gauss_seidel
from .eigen import eig, gerschgorin_disks, gerschgorin_bounds
from .interpolate import lagrange_interpolate, lagrange_basis
from .fit import fit_polynomial, eval_polynomial, rmse
from .utils import load_matrix, save_matrix, pretty_print_matrix

__all__ = [
    "lu_decompose",
    "cholesky",
    "gaussian_elimination",
    "gauss_jacobi",
    "gauss_seidel",
    "eig",
    "gerschgorin_disks",
    "gerschgorin_bounds",
    "lagrange_interpolate",
    "lagrange_basis",
    "fit_polynomial",
    "eval_polynomial",
    "rmse",
    "load_matrix",
    "save_matrix",
    "pretty_print_matrix",
]
