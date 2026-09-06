class DifferentiationMethod:
    """Root class for every numerical differentiation method."""

    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        raise NotImplementedError("Subclasses must implement derivative()")


class DividedDifference(DifferentiationMethod):
    """Common base for finite-difference-quotient methods
    (Forward, Backward, Central, Richardson)."""
    pass


class Interpolation(DifferentiationMethod):
    """Common base for polynomial-interpolation-based methods
    (Lagrange, Newton). Provides shared node-building logic."""

    def __init__(self, name, offsets=(-2, -1, 0, 1, 2)):
        super().__init__(name)
        self.offsets = offsets

    def build_nodes(self, f, x, h):
        """Build the sample points x + offset*h and evaluate f at each."""
        nodes = [x + o * h for o in self.offsets]
        values = [f.evaluate(xi) for xi in nodes]
        return nodes, values
