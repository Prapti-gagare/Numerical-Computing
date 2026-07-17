# PLAN-004: Driver Program

**Created:** 2026-04-20
**Status:** Completed
**Addresses:** Implement the user-facing driver program in `src/main.cpp` for FEATURE 4.

---

## 1. Context & motivation

FEATURE 4 is the user-facing entrypoint for the Complex Number Operations project. It uses the `complex` class and operations implemented in earlier features to read two complex numbers, compute arithmetic and utility results, and display them clearly.

Completing this feature is required to produce a working program that demonstrates the full behavior expected in the spec.

**Related sections from spec.md:**
- Project Overview: program accepts two complex numbers and displays all operations
- FEATURE 4 acceptance criteria

---

## 2. Goals

- [ ] Create `src/main.cpp`
- [ ] Prompt user for two complex numbers (real + imaginary parts)
- [ ] Display the input values clearly
- [ ] Compute and display:
  - add
  - subtract
  - multiply
  - divide
  - conjugate of first number
  - norm of both numbers
- [ ] Handle invalid input gracefully
- [ ] Compile cleanly and run end-to-end

---

## 3. Non-goals

- Automated unit tests
- Advanced input parsing beyond standard float entry
- Persistent storage or file I/O

---

## 4. Approach

1. Include `include/complex.hpp`, `<iostream>`, and `<limits>`.
2. Prompt the user for real and imaginary parts of two complex numbers.
3. Validate input using `std::cin`; if invalid, print an error and exit.
4. Use existing functions from `src/complex.cpp` for all operations.
5. Print results with clear labels and readable formatting.

---

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `src/main.cpp` with user prompts | 10 min | — |
| 2 | Use `display()` for input and result output | 5 min | 1 |
| 3 | Compute add/subtract/multiply/divide/conjugate/norm | 10 min | 1 |
| 4 | Compile and test end-to-end | 10 min | 1–3 |

**Total estimate:** ~35 minutes.

---

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|---|---|---|---|
| Invalid input breaks program | Medium | Medium | Validate `std::cin` after each read and exit cleanly on failure |
| Division by zero in driver | Low | Medium | The underlying `divide()` already handles zero division gracefully |
| Output readability | Low | Low | Use clear labels and `display()` for complex values |

---

## 7. Success criteria

✅ **Plan is complete when:**
1. `src/main.cpp` exists.
2. Program prompts the user for two complex numbers.
3. Program prints all requested operations with clear labels.
4. Program compiles cleanly with `g++ -Wall -Wextra src/main.cpp src/complex.cpp -Iinclude`.
5. Program runs end-to-end without crashing for valid input.
6. Acceptance criteria from spec.md FEATURE 4 are met.

---

## 8. References

- [spec.md — FEATURE 4](../../spec.md#feature-4--driver-program) — full feature description
- [include/complex.hpp](../../include/complex.hpp)
- [src/complex.cpp](../../src/complex.cpp)
- [plan/rules.md § 6.1–6.4](../rules.md#61-think-before-coding)
