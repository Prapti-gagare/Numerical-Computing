# Eigenvalue & Eigenvector Computation Using Power Method

## Overview

This implementation provides a robust system for computing eigenvalues and eigenvectors from augmented matrices read from text files. The solution consists of two main components:

1. **Matrix Base Class** (in `src/base.py`) - Provides core matrix operations and file I/O
2. **PowerMethod Class** (in `src/power_method.py`) - Implements the power method algorithm

## Architecture

### Class Hierarchy

```
Matrix (base class)
  └── PowerMethod (inherits from Matrix)
```

## Components

### 1. Matrix Base Class (`src/base.py`)

The `Matrix` class provides foundational operations for eigenvalue problems:

#### Key Attributes:
- `name` - Method identifier
- `matrix_A` - Primary matrix (read from inputA.txt)
- `matrix_B` - Secondary matrix/vector (read from inputB.txt)
- `augmented_matrix` - Combined matrix [A | B]
- `rows`, `cols` - Matrix dimensions

#### Key Methods:

| Method | Purpose |
|--------|---------|
| `read_matrix_from_file(filename)` | Read matrix from text file |
| `load_augmented_matrix(file_A, file_B)` | Load and combine matrices |
| `save_results_to_file(filename, eigenvalues, eigenvectors)` | Save results to text file |
| `compute_eigenvalues()` | Base method (abstract) |
| `compute_eigenvectors()` | Base method (abstract) |

#### File Format

Input files must follow this format:
```
rows cols
value1 value2 ... valueN
value1 value2 ... valueN
...
```

Example (first 3 lines of inputA.txt):
```
49 49
 -3.8004877e+002  7.1664431e+001 -1.8485281e+001 ...
  3.6037916e+001 -2.3602439e+002  2.3361444e+001 ...
```

### 2. PowerMethod Class (`src/power_method.py`)

The `PowerMethod` class implements the power iteration algorithm for finding the dominant eigenvalue and eigenvector.

#### Algorithm Overview

The power method iteratively computes:
1. Normalize initial vector: v = v / ||v||
2. Multiply: w = A * v
3. Estimate eigenvalue: λ = (v^T * A * v) / (v^T * v) [Rayleigh quotient]
4. Normalize: v = w / ||w||
5. Repeat until convergence

#### Key Methods:

| Method | Purpose |
|--------|---------|
| `normalize_vector(vector)` | Normalize vector to unit length |
| `matrix_vector_multiply(matrix, vector)` | Compute A*v |
| `compute_rayleigh_quotient(matrix, vector)` | Compute eigenvalue estimate |
| `compute_eigenvalues(matrix)` | Main eigenvalue computation |
| `compute_eigenvectors(matrix)` | Extract eigenvector |
| `solve(file_A, file_B, output_file)` | Complete pipeline |
| `get_convergence_history()` | Convergence tracking |

#### Constructor Parameters:

```python
PowerMethod(
    name="Power Method",              # Method name
    max_iterations=1000,              # Maximum iterations allowed
    tolerance=1e-6                    # Convergence tolerance
)
```

## Usage Examples

### Basic Usage

```python
from src.power_method import PowerMethod

# Create solver
solver = PowerMethod(max_iterations=1000, tolerance=1e-6)

# Solve
eigenvalue, eigenvector = solver.solve(
    file_A="inputA.txt",
    file_B="inputB.txt", 
    output_file="results.txt"
)

print(f"Eigenvalue: {eigenvalue}")
print(f"Eigenvector: {eigenvector}")
```

### Advanced Usage with Convergence Monitoring

```python
from src.power_method import PowerMethod

solver = PowerMethod(name="Custom Power Method", max_iterations=2000, tolerance=1e-8)

# Load matrices
solver.load_augmented_matrix("inputA.txt", "inputB.txt")

# Get matrix info
matrix_A = solver.get_matrix_A()
print(f"Matrix size: {len(matrix_A)} x {len(matrix_A[0])}")

# Compute eigenvalue/eigenvector
eigenvalue = solver.compute_eigenvalues()
eigenvector = solver.compute_eigenvectors()

# Monitor convergence
history = solver.get_convergence_history()
print(f"Converged in {len(history)} iterations")
print(f"Eigenvalue progression: {history[:5]} ... {history[-5:]}")

# Save results
solver.save_results_to_file("my_results.txt", eigenvalue, eigenvector)
```

## Running the Examples

### Direct Execution

Run the power method directly from the src directory:
```bash
cd src/
python3 power_method.py
```

### Using the Example Script

Run the comprehensive example:
```bash
python3 eigenvalue_example.py
```

This script demonstrates:
- Loading augmented matrices from text files
- Computing dominant eigenvalue and eigenvector
- Tracking convergence information
- Saving results to output file

## Output File Format

Results are saved in a formatted text file with the following structure:

```
============================================================
EIGENVALUES AND EIGENVECTORS RESULTS
============================================================

Method: Power Method for Dominant Eigenvalue

EIGENVALUES:
------------------------------------------------------------
λ = -428.7445940081526

EIGENVECTORS:
------------------------------------------------------------
v = [-0.4703765..., 0.1124188..., ..., -0.4703765...]

============================================================
```

## Test Results

Successfully tested with provided matrices:

**Input:**
- Matrix A: 49×49 symmetric matrix
- Vector B: 49×1 vector
- Combined: 49×50 augmented matrix

**Results:**
- **Dominant Eigenvalue**: -428.7445940081526
- **Convergence**: 38 iterations
- **Convergence Tolerance**: 1e-6
- **Eigenvector Norm**: 1.0 (normalized)

**Convergence History:**
- Initial estimate: -71.4285723184
- Final estimate: -428.7445940082
- Change: ~357.29

## Mathematical Background

### Power Method
The power method is an iterative algorithm for finding the eigenvalue with the largest absolute value (dominant eigenvalue) and its corresponding eigenvector.

**Convergence Condition:**
- Requires: |λ₁| > |λ₂| (dominant eigenvalue strictly larger)
- Rate: O(|λ₂/λ₁|^n) (geometric convergence)

### Rayleigh Quotient
$$\lambda \approx \frac{\mathbf{v}^T A \mathbf{v}}{\mathbf{v}^T \mathbf{v}}$$

This provides an accurate eigenvalue estimate and accelerates convergence.

## Performance Characteristics

| Aspect | Details |
|--------|---------|
| Time Complexity | O(n²) per iteration |
| Space Complexity | O(n²) for matrix storage |
| Convergence Rate | Geometric (exponential) |
| Suitable For | Large, sparse matrices |
| Limitation | Finds only dominant eigenvalue |

## File Structure

```
Numerical_differentiation/
├── inputA.txt                     # Matrix A (left side)
├── inputB.txt                     # Vector B (right side)
├── power_method_results.txt       # Output results
├── eigenvalue_example.py          # Example usage script
├── IMPLEMENTATION_SUMMARY.md      # Implementation details
├── README.md                      # This file
└── src/
    ├── base.py                    # Matrix base class
    ├── power_method.py            # Power method implementation
    └── ...
```

## Future Enhancements

Possible extensions to the current implementation:

1. **Inverse Power Method** - Find smallest eigenvalue
2. **Shifted Power Method** - Find eigenvalues near a target value
3. **QR Algorithm** - Compute all eigenvalues
4. **Sparse Matrix Support** - Handle sparse matrices efficiently
5. **Deflation** - Find multiple eigenvalues sequentially
6. **Complex Eigenvalues** - Support for complex matrices

## Troubleshooting

### Import Errors
If you encounter `ModuleNotFoundError`, ensure:
- Python path includes the `src/` directory
- Running scripts from the correct directory
- Using Python 3.6+

### Convergence Issues
If the method doesn't converge:
- Check if the matrix is well-conditioned
- Increase `max_iterations`
- Decrease `tolerance`
- Verify dominant eigenvalue exists (no repeated maximum eigenvalues)

### Numerical Stability
For better stability:
- Use double precision (default in Python)
- Normalize vectors after each iteration
- Use Rayleigh quotient for eigenvalue estimation

## References

- Press, W.H., et al. "Numerical Recipes" - Power Method Section
- Golub, G.H., Van Loan, C.F. "Matrix Computations" - Eigenvalue Algorithms
- Demmel, J.W. "Applied Numerical Linear Algebra"

---

**Author**: Numerical Computing Project  
**Date**: October 2026  
**Python Version**: 3.6+  
**Dependencies**: NumPy
