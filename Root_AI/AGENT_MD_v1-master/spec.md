# Complex Number Operations — Project Specification

> **Version:** 1.0
> **Created:** 2026-04-20
> **Last Updated:** 2026-04-20
> **Status:** 🟡 In Planning
>
> Living document — the AI agent updates Codebase Inventory, Decision Log,
> and Current Focus at the end of every working session. Do not edit those
> sections manually.

---

## Current Focus
<!-- The agent updates this at the start of each session. -->
<!-- Humans: glance here to see what is actively being worked on. -->

- All core features are complete. The program is validated and ready for optional polish, documentation, or automated tests.

---

## ⚠️ Critical Pre-Work (Do Before Any Feature Work)

- [ ] Set up project directory structure (`src/`, `include/`, build system)
- [ ] Verify C++11 or later compiler available and working

---

## Project Overview

This project implements a `complex` class in C++ to perform arithmetic operations on complex numbers. The implementation follows standard object-oriented design with separate header and implementation files, demonstrating core C++ concepts like constructors, operator overloading (via functions), and class design. The program accepts two complex numbers from the user, performs all supported operations, and displays results clearly.

### Problem Statement

Students and developers learning C++ need a concrete, working example of how to design a simple class, implement mathematical operations, and structure a multi-file C++ program. This project provides that foundation while teaching complex number arithmetic.

### Target Users

C++ students, educators, and learners practicing object-oriented programming fundamentals.

### Current Operational Reality (as of 2026-04-20)

Greenfield project — no code exists yet.

---

## Success Criteria (v1.0)

- [ ] `complex.hpp` declares the class with `real` and `imag` (float) members and all required functions
- [ ] `complex.cpp` implements all 7 operations (add, subtract, multiply, divide, conjugate, norm, display) correctly
- [ ] `main.cpp` accepts input for two complex numbers and demonstrates all operations with clear output
- [ ] Program compiles without warnings
- [ ] All operations produce mathematically correct results, including edge cases (division by zero handled gracefully)

---

## Constraints & Non-Negotiables

- **Team:** Single developer
- **Timeline:** No deadline; project scope is small and self-contained
- **Budget:** None
- **Compliance:** None
- **Non-negotiables:** Modular code structure (separate hpp/cpp files); clear output formatting

---

## Tech Stack

### Current (what exists today)

| Layer | Technology | Notes |
|---|---|---|
| Language | C++ (C++11 or later) | Standard library only |
| Compiler | g++ / clang | Whatever is available locally |
| Build System | g++ command line | No external build tool required for v1 |
| Testing | Manual (driver code in main) | No automated test framework |

### Target (what we are building toward)

| Layer | Technology | Notes |
|---|---|---|
| (Same as current) | | v1 has no dependencies to upgrade |

---

## Architectural Principles

- **Modularity**: Class declaration in header, implementation in cpp, driver in separate main
- **Clarity**: Function names match operations (add, subtract, multiply, divide, conjugate, norm, display); minimal external dependencies
- **Error Handling**: Gracefully handle division by zero (return error message or special value); validate basic input
- **Simplicity**: Use float precision; no templates, no advanced C++ features for v1

---

## Codebase Inventory

| File | Role | Status | Last Updated |
|---|---|---|---|
| `AGENT_MD/spec.md` | Living project specification | ✅ Active | 2026-04-20 |
| `AGENT_MD/plan/rules.md` | AI agent authoring conventions | ✅ Active | 2026-04-20 |
| `include/complex.hpp` | Complex class interface declaration | ✅ Active | 2026-04-20 |
| `src/complex.cpp` | Complex class implementation (arithmetic + utility ops) | ✅ Active | 2026-04-20 |
| `src/main.cpp` | Driver program implementation | ✅ Active | 2026-04-20 |

---

## Feature Index

| # | Feature | Status | Priority | Notes |
|---|---|---|---|---|
| 0 | Pre-Work: Setup & Structure | [ ] | P0 | Directory layout, compiler check |
| 1 | Complex Class Definition | ✅ | P0 | `include/complex.hpp` with members and signatures — COMPLETED |
| 2 | Arithmetic Operations | ✅ | P0 | add, subtract, multiply, divide in `src/complex.cpp` — COMPLETED |
| 3 | Utility Operations | ✅ | P0 | conjugate, norm, display in `src/complex.cpp` — COMPLETED |
| 4 | Driver Program | ✅ | P0 | `src/main.cpp` with user input and operation demonstrations — COMPLETED |
| 5 | Testing & Validation | ✅ | P0 | Full program validated with normal, zero, negative, divide-by-zero, and invalid input |

---

## Known Issues & Technical Debt

- None yet.

---

## Known Unknowns

- None; scope is fully specified.

---

## Decision Log

| Date | Decision | Rationale | Alternatives Considered |
|---|---|---|---|
| 2026-04-20 | Created v1.0 spec.md | Project initialisation | n/a |
| 2026-04-20 | Completed FEATURE 1 — Complex Class Definition | Implemented `include/complex.hpp` with class interface, constructors, and all 7 operation signatures; compiles cleanly with 0 errors/warnings | n/a |
| 2026-04-20 | Completed FEATURE 2 — Arithmetic Operations | Implemented add, subtract, multiply, divide in `src/complex.cpp`; all operations mathematically correct, division by zero handled gracefully | n/a |
| 2026-04-20 | Completed FEATURE 3 — Utility Operations | Implemented conjugate, norm, display in `src/complex.cpp`; divide now uses conjugate and output formatting works correctly | n/a |
| 2026-04-20 | Completed FEATURE 4 — Driver Program | Implemented `src/main.cpp` with user input, display, and full operation demonstration; verified end-to-end | n/a |
| 2026-04-20 | Completed FEATURE 5 — Testing & Validation | Validated full program with normal, zero, negative, divide-by-zero, and invalid input; fixed display formatting for NaN and zero | n/a |

---

---

# FEATURE 0 — Pre-Work: Setup & Structure

## Goal

Establish project directory structure and verify the build environment is ready.

## Tasks

- [ ] Create `src/`, `include/`, and `build/` directories
- [ ] Verify g++ (or clang) is installed and working
- [ ] Create placeholder files: `include/complex.hpp`, `src/complex.cpp`, `src/main.cpp`

## Verification

- Directory structure exists as planned
- `g++ --version` reports a working compiler
- Placeholder files can be compiled (even if empty)

---

# FEATURE 1 — Complex Class Definition

## Goal

Define the `complex` class interface with all required members and function signatures.

## Existing Code to Reference

- None yet.

## Tasks

- [ ] Declare `float real` and `float imag` members (private or public per design choice)
- [ ] Write default constructor (initialises to 0+0i)
- [ ] Write parameterized constructor (takes two floats)
- [ ] Declare all 7 operation functions: add, subtract, multiply, divide, conjugate, norm, display

## Acceptance Criteria

- [ ] Header compiles and includes no errors
- [ ] All function signatures are present and syntactically correct

---

# FEATURE 2 — Arithmetic Operations

## Goal

Implement add, subtract, multiply, and divide operations correctly.

## Existing Code to Reference

- `include/complex.hpp` (FEATURE 1)

## Tasks

- [ ] Implement `add(complex a, complex b)` — returns sum of two complex numbers
- [ ] Implement `subtract(complex a, complex b)` — returns difference
- [ ] Implement `multiply(complex a, complex b)` — returns product (using (a+bi)(c+di) = (ac-bd) + (ad+bc)i)
- [ ] Implement `divide(complex a, complex b)` — returns quotient with zero-division check

## Acceptance Criteria

- [ ] All four operations produce mathematically correct results for test cases
- [ ] Division by zero is handled (return error message or special value, do not crash)

---

# FEATURE 3 — Utility Operations

## Goal

Implement conjugate, norm, and display operations.

## Existing Code to Reference

- `include/complex.hpp` (FEATURE 1)

## Tasks

- [ ] Implement `conjugate(complex a)` — returns (real - imagi)
- [ ] Implement `norm(complex a)` — returns |a| = sqrt(real² + imag²)
- [ ] Implement `display(complex a)` — prints in readable format (e.g., "3.5 + 2.1i")

## Acceptance Criteria

- [ ] Conjugate and norm calculations are mathematically correct
- [ ] Display output is clear and readable

---

# FEATURE 4 — Driver Program

## Goal

Create a user-facing program that demonstrates all operations.

## Existing Code to Reference

- `include/complex.hpp` (FEATURE 1)
- `src/complex.cpp` (FEATURES 2–3)

## Tasks

- [ ] Prompt user to input real and imaginary parts of the first complex number
- [ ] Prompt user to input real and imaginary parts of the second complex number
- [ ] Display the two input numbers
- [ ] Perform and display: add, subtract, multiply, divide, conjugate (of first), norm (of both)
- [ ] Exit cleanly after displaying all results

## Acceptance Criteria

- [ ] Program accepts input without crashing
- [ ] All operations are performed and results displayed with clear labels
- [ ] Program compiles and runs end-to-end

---

# FEATURE 5 — Testing & Validation

## Goal

Verify all operations work correctly across normal and edge cases.

## Existing Code to Reference

- `src/main.cpp` (FEATURE 4)

## Tasks

- [ ] Test with simple numbers (e.g., 1+2i and 3+4i)
- [ ] Test with zero (e.g., 0+0i)
- [ ] Test with negative numbers
- [ ] Test division by zero and confirm graceful handling
- [ ] Verify norm calculation with known example

## Acceptance Criteria

- [ ] All test cases pass and results match manual calculations
- [ ] Edge case (division by zero) is handled without crashing
