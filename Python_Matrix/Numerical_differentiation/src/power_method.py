import math

from src.base import Matrix


class PowerMethod(Matrix):
    def __init__(self, name="Power Method", max_iterations=5000, tolerance=1e-8):
        super().__init__(name)
        self.max_iterations = max_iterations
        self.tolerance = tolerance
        self.eigenvalue = None
        self.eigenvector = None
        self.iterations = 0
        self.converged = False
        self.residual = None
        self.history = []
        self.raw_history = []      # unscaled vectors A^k * v0 (k = 0, 1, 2, ...)

    # ---------- vector / matrix helpers ----------
    def matrix_vector_multiply(self, matrix, vector):
        return [sum(a * x for a, x in zip(row, vector)) for row in matrix]

    def dot(self, u, v):
        return sum(a * b for a, b in zip(u, v))

    def norm(self, vector):
        return math.sqrt(sum(x * x for x in vector))

    def normalize_vector(self, vector):
        n = self.norm(vector)
        if n == 0.0:
            raise ValueError("Cannot normalize the zero vector")
        return [x / n for x in vector]

    def compute_rayleigh_quotient(self, matrix, vector):
        Av = self.matrix_vector_multiply(matrix, vector)
        return self.dot(vector, Av) / self.dot(vector, vector)

    # ---------- main algorithm ----------
    def run(self, initial_vector=None):
        if self.matrix_A is None:
            raise RuntimeError("Load the matrix first (load_matrix)")

        A = self.matrix_A
        n = len(A)
        if any(len(row) != n for row in A):
            raise ValueError("Matrix A must be square for the power method")

        v = initial_vector if initial_vector is not None else [1.0] * n
        raw = list(v)                            # unscaled copy: A^k * v0
        v = self.normalize_vector(v)

        self.history = []
        self.raw_history = [list(raw)]
        self.converged = False
        lam_old = 0.0

        for k in range(1, self.max_iterations + 1):
            w = self.matrix_vector_multiply(A, v)
            lam = self.dot(v, w)                 # Rayleigh quotient (|v| = 1)
            w_norm = self.norm(w)
            if w_norm == 0.0:                    # v is in the null space: lambda = 0
                lam, v, self.converged, self.iterations = 0.0, v, True, k
                self.history.append(lam)
                break

            v_new = [x / w_norm for x in w]
            self.history.append(lam)

            # unscaled iteration (stop recording before the numbers overflow)
            if max(abs(x) for x in raw) < 1e150:
                raw = self.matrix_vector_multiply(A, raw)
                self.raw_history.append(list(raw))

            # sign of the dominant eigenvalue: if lambda < 0, w flips sign each step.
            # Compare v_new with +v or -v depending on the sign of lambda.
            sign = 1.0 if lam >= 0 else -1.0
            vec_diff = self.norm([a - sign * b for a, b in zip(v_new, v)])

            v = v_new
            self.iterations = k

            if abs(lam - lam_old) <= self.tolerance * max(1.0, abs(lam)) \
                    and vec_diff <= math.sqrt(self.tolerance):
                self.converged = True
                break
            lam_old = lam

        # final, consistent estimate from the last vector
        Av = self.matrix_vector_multiply(A, v)
        lam = self.dot(v, Av)
        self.residual = self.norm([a - lam * x for a, x in zip(Av, v)])

        # make the eigenvector sign deterministic: largest component positive
        idx = max(range(n), key=lambda i: abs(v[i]))
        if v[idx] < 0:
            v = [-x for x in v]

        self.eigenvalue = lam
        self.eigenvector = v
        return lam, v

    def compute_eigenvalues(self):
        if self.eigenvalue is None:
            self.run()
        return self.eigenvalue

    def compute_eigenvectors(self):
        if self.eigenvector is None:
            self.run()
        return self.eigenvector

    def get_convergence_history(self):
        return self.history

    def get_raw_vectors(self):
        """Unscaled vectors: (1,1,1), A*(1,1,1), A^2*(1,1,1), ... (no normalization)."""
        return self.raw_history

    def save_iterations_to_file(self, filename):
        with open(filename, "w") as f:
            f.write("Unscaled power iteration: v_k = A * v_(k-1)\n")
            f.write("-" * 60 + "\n")
            for k, vec in enumerate(self.raw_history):
                f.write(f"k={k:<3} (" + ", ".join(f"{x:.10g}" for x in vec) + ")\n")

    def solve(self, file_A, output_file=None):
        self.load_matrix(file_A)
        lam, v = self.run()
        if output_file:
            self.save_results_to_file(output_file, lam, v)
        return lam, v