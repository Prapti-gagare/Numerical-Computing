# PLAN-001: Complex Class Definition

**Created:** 2026-04-20
**Status:** Completed
**Addresses:** Implement the header file declaring the `complex` class interface with members and function signatures required by FEATURE 1.

---

## 1. Context & motivation

FEATURE 1 establishes the foundation for the entire Complex Number Operations project. The class declaration in `include/complex.hpp` is the contract that the implementation (`src/complex.cpp`) will fulfill and that the driver program (`src/main.cpp`) will use.

This plan is the first substantive implementation task and unblocks FEATURES 2–5 (arithmetic, utility operations, and driver).

**Related sections from spec.md:**
- Project Overview: modular structure with separate hpp/cpp files
- Architectural Principles: modularity and clarity
- FEATURE 1 acceptance criteria

---

## 2. Goals

- [ ] **Header file created and syntactically valid:** `include/complex.hpp` exists, includes proper guard macros, and compiles without warnings.
- [ ] **Class interface complete:** `complex` class declared with `float real` and `float imag` members and all 7 operation function signatures.
- [ ] **Constructors implemented:** Default constructor (0+0i) and parameterized constructor (takes two floats) declared.
- [ ] **Documentation present:** Brief inline comments explaining member purpose and constructor behaviour.
- [ ] **Verified compilable:** Header compiles standalone (`g++ -c include/complex.hpp`) with no errors or warnings.

---

## 3. Non-goals

- Implementation bodies for any functions (deferred to FEATURES 2–3).
- Main function or driver code (deferred to FEATURE 4).
- Automated tests (deferred to FEATURE 5).
- Operator overloads (`operator+`, `operator*`, etc.). All operations use named functions only.
- Advanced C++ features (templates, inheritance, exceptions).

---

## 4. Approach

### 4.1 Design decisions

**Member visibility:** Members (`real`, `imag`) will be **public** for simplicity and pedagogical clarity. A teaching example benefits from direct access; encapsulation can be revisited in a later iteration if desired.

**Function signatures:** All 7 operations will be **free functions** (not class methods), taking `complex` arguments and returning results. This keeps the class minimal and makes mathematical operations read naturally (e.g., `add(a, b)` vs. `a.add(b)`).

```cpp
// Example signatures (not full code):
complex add(const complex& a, const complex& b);
complex conjugate(const complex& a);
float norm(const complex& a);
void display(const complex& a);
```

**Why?** This aligns with the project's pedagogical goal: the class is a data container with constructors; operations are separate. It's simpler for beginners and avoids confusion about when to use `.` vs `::`.

### 4.2 File structure

```
include/
└── complex.hpp
    ├── Include guards (#ifndef, #define, #endif)
    ├── Class declaration block
    │   ├── Members (real, imag)
    │   ├── Default constructor
    │   └── Parameterized constructor
    └── Function declarations block
        ├── add, subtract, multiply, divide
        ├── conjugate, norm, display
        └── (All signatures only; no bodies)
```

### 4.3 Alternatives considered

| Alternative | Why not chosen |
|---|---|
| **Member functions** (e.g., `a.add(b)`) | Less clear for mathematical operations; requires method syntax. Free functions are more natural. |
| **Private members + getters/setters** | Overkill for a teaching example; adds boilerplate without clear benefit. |
| **Templates** (generic `complex<T>`) | Out of scope for v1; would complicate the code for a learner. Float is concrete and sufficient. |
| **Header + body inline** | Would violate the spec's requirement for separate `.hpp` and `.cpp` files. |

---

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `include/complex.hpp` with include guards and outline | 15 min | — |
| 2 | Declare `complex` class with `float real` and `float imag` members | 10 min | 1 |
| 3 | Declare default constructor | 5 min | 2 |
| 4 | Declare parameterized constructor | 5 min | 2 |
| 5 | Declare 4 arithmetic function signatures (add, subtract, multiply, divide) | 10 min | 2 |
| 6 | Declare 3 utility function signatures (conjugate, norm, display) | 10 min | 2 |
| 7 | Compile header standalone and verify no errors | 10 min | 1–6 |

**Total estimate:** ~65 minutes.

---

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|---|---|---|---|---|
| Include guard name collision | Low | Low | Use a long, unique guard name: `COMPLEX_NUMBER_OPERATIONS_COMPLEX_HPP` |
| Missing `#include` directives needed for function signatures | Medium | Medium | Verify that `float` and `void` don't require includes; test compile after every signature block. |
| Asymmetry between declared functions and acceptance criteria | Low | Medium | Review acceptance criteria before compiling: all 7 operations declared? Constructors present? |
| Compiler warnings (unused parameters, pedantic style) | Low | Low | Compile with `-Wall -Wextra` to catch issues early. Add comments if warnings appear. |

---

## 7. Success criteria

✅ **Plan is complete when:**
1. File `include/complex.hpp` exists.
2. Include guards are present and correct.
3. Class `complex` declared with public `float real` and `float imag` members.
4. Default constructor declared: `complex();`
5. Parameterized constructor declared: `complex(float, float);`
6. All 7 function signatures declared: `add`, `subtract`, `multiply`, `divide`, `conjugate`, `norm`, `display`.
7. File compiles with `g++ -c include/complex.hpp` with 0 errors and 0 warnings.
8. Acceptance criteria from spec.md FEATURE 1 are met:
   - [ ] Header compiles and includes no errors
   - [ ] All function signatures are present and syntactically correct

---

## 8. References

- [spec.md — FEATURE 1](../../spec.md#feature-1--complex-class-definition) — full feature description
- [spec.md — Architectural Principles](../../spec.md#architectural-principles) — design philosophy
- [spec.md — Project Overview](../../spec.md#project-overview) — context
- [C++ class syntax reference](https://en.cppreference.com/w/cpp/language/class) — for syntax verification
- [plan/rules.md § 6.1–6.4](../rules.md#61-think-before-coding) — AI agent execution guidelines
