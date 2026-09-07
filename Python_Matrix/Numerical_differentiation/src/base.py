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
