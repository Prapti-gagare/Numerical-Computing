# Matrix Library — Python Port Specification

> **Version:** 1.0
> **Created:** 2026-08-13
> **Last Updated:** 2026-08-13
> **Status:** 🟡 Draft (awaiting review)

This document specifies the scope, API, testing, and deliverables for porting the C++ `Matrix/` library in this repository to idiomatic Python using `numpy`/`scipy`.

## Goal

Port core numerical linear algebra and helper algorithms from `Matrix/Include` and `Matrix/src` into a well-organised Python package `matrixpy` that:

- Provides the same numerical functionality (LU, Gaussian elimination, iterative solvers, eigenvalue routines, interpolation, curve fitting, linear system helpers).
- Is tested, documented, and easy to import/use from other Python projects.
- Uses `numpy` for arrays and `scipy` for advanced routines where appropriate.

## Scope

- Translate and adapt the following components (non-exhaustive):
	- Decompositions: `lu`, `cholsky`, `crouts`, `dolittle` → `matrixpy.decomposition` module
	- Solvers: `gaussian`, `gauss_jacobi`, `gauss_seidle` → `matrixpy.solvers` module
	- Eigenvalue: `Eigenvalue`, `gerschgorin` → `matrixpy.eigen` module
	- Interpolation & fitting: `interpolation`, `lagrange`, `leastsquare`, `curvefitting` → `matrixpy.interpolate` / `matrixpy.fit`
	- Utilities: `matrix`, `LinearSystem`, `iterative_method`, `lu` helpers → `matrixpy.utils`

Excluded: CLI and unrelated build/tooling files; unless needed for examples.

## Requirements & Dependencies

- Python 3.10+ (3.11 recommended)
- numpy
- scipy
- pytest (unit tests)
- black/isort (optional formatting)
- typing (mypy-friendly annotations)

## API & Design Guidelines

- Use numpy.ndarray as primary data representation.
- Functions return tuples where appropriate (e.g., `lu_decompose(A) -> (L, U, P)`)
- Raise `ValueError` for invalid inputs; document domain restrictions.
- Provide a small set of high-level convenience functions matching common usage patterns.

Module layout (proposal):

- `matrixpy/__init__.py` — package exports
- `matrixpy/decomposition.py` — `lu`, `cholsky`, `crout`, `dolittle`
- `matrixpy/solvers.py` — `gaussian_elimination`, `gauss_jacobi`, `gauss_seidel`
- `matrixpy/eigen.py` — eigenvalue helpers and wrappers
- `matrixpy/interpolate.py` — interpolation, Lagrange
- `matrixpy/fit.py` — least squares, curve fitting helpers
- `matrixpy/utils.py` — small matrix utilities and I/O for examples
- `tests/` — pytest test cases mirroring C++ example outputs

## Testing & Validation

- Unit tests for each module using `pytest`.
- Numerical validation: where the original C++ library includes example outputs (in `Matrix/output`), create test cases that compare results within a relative tolerance (e.g., rtol=1e-8 for double-precision algorithms).
- Add small integration tests that solve sample linear systems and check residual norms.

## Deliverables

- `matrixpy` package with the modules above.
- `tests/` with coverage for core algorithms.
- `examples/` reproducing one or two existing C++ example runs.
- `README.md` with quick usage and install instructions.

## Acceptance Criteria

- All core algorithms ported and module-level unit tests present.
- Tests pass locally with `pytest` and numeric outputs match C++ references within acceptable tolerances.
- Code is formatted and documented (docstrings for public functions).

## Risk & Notes

- Some C++ implementations may rely on in-place optimisations; Python/Numpy implementations may differ in performance—focus on correctness first and optimise selectively.
- Consider delegating heavy linear algebra to `scipy.linalg` for robustness where appropriate.

## Timeline (proposal)

1. Spec review and sign-off (this document) — review by user
2. Create detailed plan files (per your approval)
3. Implement modules incrementally, starting with `decomposition` and `solvers` (iterative + direct)
4. Add tests and examples
5. Final report and delivery

---

Please review this draft. If you approve, say “OK spec” and I will generate the plan files next.
