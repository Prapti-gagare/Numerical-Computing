# PLAN-001: Port `Matrix/` C++ library to Python (`matrixpy`)

## Overview

This plan describes the steps, milestones, owners, and acceptance criteria for porting the `Matrix/` C++ numerical library to a Python package `matrixpy`.

## Objectives

- Produce a correct, tested, and documented Python implementation of the core C++ algorithms.
- Keep public APIs simple and numpy-first.
- Provide tests that validate numerical results against C++ examples.

## Owner

- Single developer: Assigned to repository maintainer (you).

## Milestones

1. Plan sign-off - user approves this plan (this file).
2. Setup & scaffolding - create package layout, `requirements.txt`, and testing skeleton.
3. Implement `decomposition` and `solvers` modules; add unit tests.
4. Implement `eigen`, `interpolate`, and `fit` modules; add unit tests.
5. Implement `utils`, examples, and packaging (`README`, `setup.cfg`/`pyproject.toml`).
6. Integration tests and numeric validation against `Matrix/output`.
7. Final report and delivery.

## Tasks (by milestone)

### 2 - Setup & scaffolding
- Create package `matrixpy/` and `tests/` directories.
- Add `requirements.txt` with `numpy`, `scipy`, `pytest`.
- Add CI skeleton (optional).

### 3 - Decomposition & Solvers
- Port `cholsky`, `crouts`, `dolittle`, `lu` into `matrixpy/decomposition.py`.
- Implement `gaussian_elimination`, `gauss_jacobi`, `gauss_seidel` in `matrixpy/solvers.py`.
- Add unit tests for each function (edge cases, singular matrices).

### 4 - Eigen, Interpolation & Fit
- Implement `matrixpy/eigen.py` wrapping/replicating `Eigenvalue` and `gerschgorin` logic.
- Implement `matrixpy/interpolate.py` (Lagrange) and `matrixpy/fit.py` (least-squares, curve fitting).
- Add tests comparing to known analytic solutions or `scipy` equivalents.

### 5 - Utils, Examples, Packaging
- Implement `matrixpy/utils.py` and example scripts replicating C++ examples.
- Add `README.md` with quickstart and example commands.

### 6 - Integration & Validation
- Create tests that run example inputs from `Matrix/output` and assert results within tolerances.
- Run `pytest` and fix issues.

### 7 - Final Report
- Produce a short report summarizing what was ported, test results, and numeric discrepancies.

## Schedule (estimate)

- Setup & scaffolding: 1 day
- Decomposition & solvers: 3 days
- Eigen/interpolate/fit: 3 days
- Utils/examples/packaging: 1 day
- Integration, testing, report: 1-2 days

## Acceptance Criteria

- Each module has unit tests and passes locally.
- Numeric results match C++ examples within accepted tolerances (documented per-test).
- Package imports cleanly and includes usage examples in `README.md`.

## Risks & Mitigations

- Performance differences: document and rely on `scipy` where performance/robustness matters.
- Missing reference outputs: if C++ output is absent, validate against `scipy` or analytic cases.

---

When you approve this plan, reply with "OK plan" and I will generate the corresponding report template files under `plan/reports/`.
