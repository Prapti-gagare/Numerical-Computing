# PLAN-006-Integration_Testing: Validation and Final Checks

## Goal

Validate the Python implementation against C++ example outputs and run full test suite.

## Tasks

- Create integration tests that run example inputs from `Matrix/output` and compare results within defined tolerances.
- Run `pytest` and collect failures; fix issues.
- Prepare final checklist for reporting (tests passed, numeric diffs documented).

## Acceptance Criteria

- All tests pass or have documented, acceptable numeric differences.

## Estimate

- 1-2 days
