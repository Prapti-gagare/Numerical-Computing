# PLAN-003-Solvers: Gaussian elimination & Iterative solvers

## Goal

Implement direct and iterative linear system solvers in `matrixpy/solvers.py`.

## Tasks

- Implement `gaussian_elimination(A, b)` returning solution vector and residual.
- Implement `gauss_jacobi(A, b, tol, maxiter)` and `gauss_seidel(A, b, tol, maxiter)`.
- Add convergence tests and edge-case tests (non-convergence, singular matrices).

## Acceptance Criteria

- Solvers produce correct solutions within tolerances; iterative solvers respect stopping criteria.

## Estimate

- 2-3 days
