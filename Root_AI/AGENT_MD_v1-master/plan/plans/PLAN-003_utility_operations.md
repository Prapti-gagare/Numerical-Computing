# PLAN-003: Utility Operations

**Created:** 2026-04-20
**Status:** Completed
**Addresses:** Implement conjugate, norm, and display operations in src/complex.cpp for FEATURE 3.

---

## 1. Context & motivation

FEATURES 1 and 2 established the class interface and arithmetic operations. FEATURE 3 completes the implementation by adding the utility operations (conjugate, norm, display) to `src/complex.cpp`. These are essential for the driver program (FEATURE 4) to demonstrate all required functionality and for the arithmetic operations (like divide) that depend on conjugate.

This plan finalizes the implementation file and unblocks the complete working program.

**Related sections from spec.md:**
- Project Overview: all 7 operations needed for demonstration
- Architectural Principles: clarity in function naming and output formatting
- FEATURE 3 acceptance criteria

---

## 2. Goals

- [ ] **Utility functions implemented:** `conjugate()`, `norm()`, `display()` added to `src/complex.cpp`
- [ ] **Conjugate operation correct:** `conjugate(a)` returns (a.real, -a.imag)
- [ ] **Norm operation correct:** `norm(a)` returns sqrt(a.real² + a.imag²)
- [ ] **Display operation correct:** `display(a)` prints in readable format (e.g., "3.5 + 2.1i")
- [ ] **Compiles cleanly:** Updated `src/complex.cpp` compiles without errors or warnings
- [ ] **Integration verified:** All functions work together (e.g., divide uses conjugate)

---

## 3. Non-goals

- Arithmetic operations — already implemented in FEATURE 2
- Driver program (main.cpp) — deferred to FEATURE 4
- Automated tests — deferred to FEATURE 5
- Input validation or advanced formatting

---

## 4. Approach

### 4.1 Design decisions

**Function signatures:** Match exactly the declarations in `include/complex.hpp` — free functions with appropriate return types.

**Mathematical formulas:**
- Conjugate: `(a.real, -a.imag)`
- Norm: `sqrt(a.real * a.real + a.imag * a.imag)` (requires `<cmath>`)
- Display: Print to `std::cout` in format "real ± imag*i" (requires `<iostream>`)

**Display formatting:** Handle positive/negative imaginary parts correctly; use fixed precision if needed, but keep simple for now.

**Dependencies:** Add `#include <cmath>` for `sqrt()`; `<iostream>` already included.

### 4.2 File updates

Append to existing `src/complex.cpp`:
```
#include <cmath>  // For sqrt()

// ... existing code ...

// ============================================================================
// Utility Operations
// ============================================================================

complex conjugate(const complex& a) { ... }
float norm(const complex& a) { ... }
void display(const complex& a) { ... }
```

### 4.3 Alternatives considered

| Alternative | Why not chosen |
|---|---|
| **Method syntax** | Inconsistent with arithmetic operations; spec uses free functions |
| **Return string from display** | Less flexible than direct output; spec specifies "prints to standard output" |
| **Custom formatting** | Overkill; simple ± format is clear and standard |

---

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Add `#include <cmath>` to `src/complex.cpp` | 2 min | — |
| 2 | Implement `conjugate()` function | 5 min | 1 |
| 3 | Implement `norm()` function | 5 min | 1 |
| 4 | Implement `display()` function | 10 min | 1 |
| 5 | Compile updated `complex.cpp` and verify no errors | 5 min | 1–4 |
| 6 | Manual verification of utility operations | 10 min | 5 |

**Total estimate:** ~37 minutes.

---

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|---|---|---|---|---|
| Missing include for sqrt() | Low | Medium | Add `#include <cmath>` explicitly; compile after each function |
| Display formatting issues (negative imag) | Low | Low | Test with positive and negative imaginary parts |
| Integration issues with existing code | Low | Low | Compile incrementally; verify divide still works |

---

## 7. Success criteria

✅ **Plan is complete when:**
1. File `src/complex.cpp` updated with 3 new functions.
2. `#include <cmath>` added.
3. All functions implemented: `conjugate`, `norm`, `display`.
4. File compiles with `g++ -c src/complex.cpp -Iinclude` → 0 errors, 0 warnings.
5. Manual verification passes:
   - Conjugate: conjugate(3+4i) = 3-4i
   - Norm: norm(3+4i) = 5.0
   - Display: prints "3 + 4i" for positive imag, "3 - 4i" for negative imag
6. Acceptance criteria from spec.md FEATURE 3 are met:
   - [ ] Conjugate and norm calculations are mathematically correct
   - [ ] Display output is clear and readable

---

## 8. References

- [spec.md — FEATURE 3](../../spec.md#feature-3--utility-operations) — full feature description
- [spec.md — Architectural Principles](../../spec.md#architectural-principles) — design philosophy
- [include/complex.hpp](../../include/complex.hpp) — function declarations to implement
- [src/complex.cpp](../../src/complex.cpp) — existing implementation to extend
- [plan/rules.md § 6.1–6.4](../rules.md#61-think-before-coding) — AI agent execution guidelines
