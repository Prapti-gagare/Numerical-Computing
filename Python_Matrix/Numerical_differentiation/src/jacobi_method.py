"""Jacobi rotation method for real symmetric matrices."""
import math
from src.base import Matrix


class JacobiMethod(Matrix):
    def __init__(self, tolerance=1e-8):
        super().__init__('Jacobi Rotation Method')
        if not math.isfinite(tolerance) or tolerance <= 0:
            raise ValueError('Tolerance must be positive and finite')
        self.tolerance = tolerance
        self.iterations = 0
        self.converged = False

    def run(self):
        if self.matrix_A is None:
            raise RuntimeError('Load the matrix first')
        B = [row[:] for row in self.matrix_A]
        n = len(B)
        if n == 0 or any(len(row) != n for row in B):
            raise ValueError('Matrix must be square')
        for i in range(n):
            for j in range(i + 1, n):
                if not math.isclose(B[i][j], B[j][i], rel_tol=1e-10, abs_tol=1e-10):
                    raise ValueError('Matrix must be symmetric')
        V = [[float(i == j) for j in range(n)] for i in range(n)]
        self.iterations = 0
        self.converged = False
        while True:
            largest = 0.0
            p = q = 0
            for i in range(n):
                for j in range(i + 1, n):
                    if abs(B[i][j]) > largest:
                        largest, p, q = abs(B[i][j]), i, j
            if largest < self.tolerance:
                self.converged = True
                break
            # Rotation with B'kp = c*Bkp - s*Bkq.
            theta = 0.5 * math.atan2(-2 * B[p][q], B[q][q] - B[p][p])
            c, s = math.cos(theta), math.sin(theta)
            app, aqq, apq = B[p][p], B[q][q], B[p][q]
            B[p][p] = c*c*app - 2*c*s*apq + s*s*aqq
            B[q][q] = s*s*app + 2*c*s*apq + c*c*aqq
            B[p][q] = B[q][p] = 0.0
            for k in range(n):
                if k != p and k != q:
                    bkp, bkq = B[k][p], B[k][q]
                    B[k][p] = B[p][k] = c*bkp - s*bkq
                    B[k][q] = B[q][k] = s*bkp + c*bkq
            for k in range(n):
                vkp, vkq = V[k][p], V[k][q]
                V[k][p] = c*vkp - s*vkq
                V[k][q] = s*vkp + c*vkq
            self.iterations += 1
        self.final_matrix = B
        eigenvalues = [B[i][i] for i in range(n)]
        eigenvectors = [[V[i][j] for i in range(n)] for j in range(n)]
        return eigenvalues, eigenvectors
