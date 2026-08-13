# PLAN-004-Eigen_Interpolate_Fit: Eigenvalues, Interpolation, Curve Fitting

## Goal

Provide eigenvalue helpers, interpolation (Lagrange), and least-squares/curve-fitting utilities.

## Tasks

- Implement `eigen` helpers and `gerschgorin` region computation in `matrixpy/eigen.py`.
- Implement `lagrange_interpolate` in `matrixpy/interpolate.py`.
- Implement least-squares and simple curve-fitting wrappers in `matrixpy/fit.py` (use `numpy.linalg.lstsq` / `scipy.optimize` as needed).
- Add unit tests comparing results to `scipy` or analytic cases.

## Acceptance Criteria

- Eigen routines return expected eigenvalues/vectors for test matrices; interpolation/fit routines match reference outputs within tolerance.

## Estimate

- 3 days
