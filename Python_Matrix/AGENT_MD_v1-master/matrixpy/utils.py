"""Utility functions for matrix operations and I/O."""
import numpy as np


def load_matrix(filename):
    """Load a matrix from a text file (space or tab-delimited)."""
    return np.loadtxt(filename, dtype=float)


def save_matrix(filename, A):
    """Save a matrix to a text file."""
    np.savetxt(filename, A, fmt="%.6e")


def pretty_print_matrix(A, name="Matrix"):
    """Print a matrix in a readable format."""
    print(f"\n{name}:")
    print(A)
