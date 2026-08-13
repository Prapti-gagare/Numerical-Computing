# PLAN-002-Decomposition: LU, Cholesky, Crout, Dolittle

## Goal

Port decomposition algorithms into `matrixpy/decomposition.py` with clear APIs and tests.

## Tasks

- Implement `lu_decompose(A) -> (L, U, P)`.
- Implement `cholesky(A) -> L`.
- Implement Crout and Dolittle variants or provide documented wrappers to `lu_decompose`.
- Add unit tests including singular and positive-definite cases.

## Acceptance Criteria

- Functions return numpy arrays and pass unit tests comparing to `scipy.linalg` where applicable.

## Estimate

- 2-3 days
