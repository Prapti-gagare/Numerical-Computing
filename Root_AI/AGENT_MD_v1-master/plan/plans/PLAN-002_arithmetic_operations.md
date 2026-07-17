# PLAN-002: Arithmetic Operations

**Created:** 2026-04-20
**Status:** Completed
**Addresses:** Implement add, subtract, multiply, and divide operations in src/complex.cpp for FEATURE 2.

---

## 1. Context & motivation

FEATURE 1 established the class interface in `include/complex.hpp`. FEATURE 2 builds on this by implementing the core arithmetic operations (add, subtract, multiply, divide) in `src/complex.cpp`. These are the fundamental mathematical operations that the driver program (FEATURE 4) will use to demonstrate complex number arithmetic.

This plan unblocks FEATURE 4 (driver program) and is a prerequisite for the complete working program.

**Related sections from spec.md:**
- Project Overview: modular structure with separate hpp/cpp files
- Architectural Principles: clarity and error handling (especially for division by zero)
- FEATURE 2 acceptance criteria

---

## 2. Goals

- [ ] **Implementation file created:** `src/complex.cpp` exists with all 4 arithmetic function implementations
- [ ] **Add operation correct:** `add(a, b)` returns mathematically correct sum (a.real + b.real, a.imag + b.imag)
- [ ] **Subtract operation correct:** `subtract(a, b)` returns mathematically correct difference (a.real - b.real, a.imag - b.imag)
- [ ] **Multiply operation correct:** `multiply(a, b)` implements (a+bi)(c+di) = (ac-bd) + (ad+bc)i
- [ ] **Divide operation correct:** `divide(a, b)` implements complex division with zero-division handling
- [ ] **Compiles cleanly:** `src/complex.cpp` compiles with `include/complex.hpp` without errors or warnings
- [ ] **Mathematically verified:** Manual verification of operations with known examples (e.g., (1+2i) + (3+4i) = 4+6i)

---

## 3. Non-goals

- Utility operations (conjugate, norm, display) — deferred to FEATURE 3
- Driver program (main.cpp) — deferred to FEATURE 4
- Automated tests — deferred to FEATURE 5
- Advanced C++ features (exceptions, templates)
- Input/output handling (user prompts) — that's for main.cpp

---

## 4. Approach

### 4.1 Design decisions

**Function signatures:** Match exactly the declarations in `include/complex.hpp` — free functions taking `const complex&` arguments and returning `complex` results.

**Mathematical formulas:**
- Add: `(a.real + b.real, a.imag + b.imag)`
- Subtract: `(a.real - b.real, a.imag - b.imag)`
- Multiply: `(a.real*b.real - a.imag*b.imag, a.real*b.imag + a.imag*b.real)`
- Divide: `(a*b.conjugate()) / |b|²`, with special handling for zero denominator

**Division by zero:** Return a special value (e.g., complex with NaN or INF) and print an error message to stderr. Do not crash the program.

**File structure:**
```
src/complex.cpp
├── #include "complex.hpp"
├── complex::complex() { ... }  // Constructor implementations
├── complex::complex(float r, float i) { ... }
├── complex add(const complex& a, const complex& b) { ... }
├── complex subtract(const complex& a, const complex& b) { ... }
├── complex multiply(const complex& a, const complex& b) { ... }
├── complex divide(const complex& a, const complex& b) { ... }
```

### 4.2 Alternatives considered

| Alternative | Why not chosen |
|---|---|
| **Method syntax** (a.add(b)) | Less natural for mathematical operations; spec uses free functions |
| **Return by value** | Correct for small structs; no performance issue for complex numbers |
| **Exceptions for division by zero** | Overkill for this simple program; spec prefers graceful handling |
| **Inline implementations in header** | Violates modular design; implementations belong in .cpp |

---

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `src/complex.cpp` with include and constructor implementations | 10 min | — |
| 2 | Implement `add()` function | 5 min | 1 |
| 3 | Implement `subtract()` function | 5 min | 1 |
| 4 | Implement `multiply()` function | 10 min | 1 |
| 5 | Implement `divide()` function with zero-division check | 15 min | 1 |
| 6 | Compile `complex.cpp` with header and verify no errors | 10 min | 1–5 |
| 7 | Manual verification of operations with test cases | 10 min | 6 |

**Total estimate:** ~65 minutes.

---

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|---|---|---|---|---|
| Mathematical formula errors | Medium | High | Double-check formulas against standard complex arithmetic; test with known examples |
| Division by zero not handled gracefully | Low | Medium | Implement check for zero denominator; return special value and log error |
| Compilation errors (missing includes, syntax) | Low | Low | Compile incrementally after each function; use `g++ -Wall -Wextra` |
| Constructor implementations forgotten | Low | Low | Include constructors in task 1; verify against header declarations |

---

## 7. Success criteria

✅ **Plan is complete when:**
1. File `src/complex.cpp` exists.
2. All 4 arithmetic functions implemented: `add`, `subtract`, `multiply`, `divide`.
3. Constructor implementations present: `complex::complex()` and `complex::complex(float, float)`.
4. File compiles with `g++ -c src/complex.cpp -Iinclude` → 0 errors, 0 warnings.
5. Manual verification passes for test cases:
   - Add: (1+2i) + (3+4i) = 4+6i
   - Subtract: (5+3i) - (2+1i) = 3+2i
   - Multiply: (1+2i) * (3+4i) = (1*3 - 2*4) + (1*4 + 2*3)i = -5 + 10i
   - Divide: (4+2i) / (2+0i) = 2+1i; (1+0i) / (0+0i) = error handled
6. Acceptance criteria from spec.md FEATURE 2 are met:
   - [ ] All four operations produce mathematically correct results for test cases
   - [ ] Division by zero is handled (return error message or special value, do not crash)

---

## 8. References

- [spec.md — FEATURE 2](../../spec.md#feature-2--arithmetic-operations) — full feature description
- [spec.md — Architectural Principles](../../spec.md#architectural-principles) — design philosophy
- [include/complex.hpp](../../include/complex.hpp) — function declarations to implement
- [Complex number arithmetic](https://en.wikipedia.org/wiki/Complex_number#Arithmetic_operations) — mathematical formulas
- [plan/rules.md § 6.1–6.4](../rules.md#61-think-before-coding) — AI agent execution guidelines
