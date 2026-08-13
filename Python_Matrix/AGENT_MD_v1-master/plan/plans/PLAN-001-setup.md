# PLAN-001-Setup: Scaffolding and Environment

## Goal

Create the Python package layout, dependency manifest, and testing skeleton so implementation work can proceed.

## Owner

- You (repository maintainer)

## Tasks

- Create `matrixpy/` package with `__init__.py`.
- Add `requirements.txt` containing `numpy`, `scipy`, `pytest`.
- Create `tests/` directory and CI skeleton (optional).
- Add `pyproject.toml` or minimal packaging files.

## Acceptance Criteria

- Project imports `matrixpy` locally.
- `pytest` runs with no tests (or initial smoke tests) without errors.

## Estimate

- 0.5-1 day
