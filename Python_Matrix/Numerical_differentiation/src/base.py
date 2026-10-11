class DifferentiationMethod:

    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        raise NotImplementedError("Subclasses must implement derivative()")


class DividedDifference(DifferentiationMethod):
    pass


class Interpolation(DifferentiationMethod):

    def __init__(self, name, offsets=(-2, -1, 0, 1, 2)):
        super().__init__(name)
        self.offsets = offsets

    def build_nodes(self, f, x, h):
        nodes = [x + o * h for o in self.offsets]
        values = [f.evaluate(xi) for xi in nodes]
        return nodes, values


class IntegrationMethod:

    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

    def integrate(self, f, a, b, n):
        raise NotImplementedError("Subclasses must implement integrate()")


class Matrix:
    """Base class for matrix problems read from a single text file.

    File format (e.g. inputA.txt):
        rows cols
        a11 a12 ... a1n
        ...
    Values may be split over lines in any way; they are read in row-major order.
    """

    def __init__(self, name):
        self.name = name
        self.matrix_A = None
        self.rows = 0
        self.cols = 0

    def get_name(self):
        return self.name

    def read_matrix_from_file(self, filename):
        with open(filename, "r") as f:
            tokens = f.read().split()

        if len(tokens) < 2:
            raise ValueError(f"{filename}: missing 'rows cols' header")

        rows, cols = int(tokens[0]), int(tokens[1])
        values = [float(t) for t in tokens[2:]]

        if len(values) != rows * cols:
            raise ValueError(
                f"{filename}: header says {rows}x{cols} = {rows * cols} values "
                f"but found {len(values)}"
            )

        return [values[i * cols:(i + 1) * cols] for i in range(rows)]

    def load_matrix(self, filename):
        self.matrix_A = self.read_matrix_from_file(filename)
        self.rows = len(self.matrix_A)
        self.cols = len(self.matrix_A[0])
        return self.matrix_A

    def get_matrix_A(self):
        return self.matrix_A

    def save_results_to_file(self, filename, eigenvalues, eigenvectors):
        with open(filename, "w") as f:
            f.write("=" * 60 + "\n")
            f.write("EIGENVALUES AND EIGENVECTORS RESULTS\n")
            f.write("=" * 60 + "\n\n")
            f.write(f"Method: {self.name}\n\n")
            f.write("EIGENVALUES:\n" + "-" * 60 + "\n")
            f.write(f"lambda = {eigenvalues!r}\n\n")
            f.write("EIGENVECTORS:\n" + "-" * 60 + "\n")
            for i, x in enumerate(eigenvectors):
                f.write(f"v[{i + 1:>3}] = {x:.10e}\n")
            f.write("\n" + "=" * 60 + "\n")

    def compute_eigenvalues(self):
        raise NotImplementedError("Subclasses must implement compute_eigenvalues()")

    def compute_eigenvectors(self):
        raise NotImplementedError("Subclasses must implement compute_eigenvectors()")
