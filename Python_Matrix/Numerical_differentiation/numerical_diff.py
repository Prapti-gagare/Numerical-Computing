from abc import ABC, abstractmethod


class TestFunction:
    def __init__(self, name, function, exact_derivative):
        self.name = name
        self.function = function
        self.exact_derivative = exact_derivative

    def get_name(self):
        return self.name

    def evaluate(self, x):
        return self.function(x)

    def exact(self, x):
        return self.exact_derivative(x)


class DifferenceMethod(ABC):
    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

    @abstractmethod
    def derivative(self, f, x, h):
        pass


class ForwardDifference(DifferenceMethod):
    def __init__(self):
        super().__init__("Forward")

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x)) / h


class BackwardDifference(DifferenceMethod):
    def __init__(self):
        super().__init__("Backward")

    def derivative(self, f, x, h):
        return (f.evaluate(x) - f.evaluate(x - h)) / h


class CentralDifference(DifferenceMethod):
    def __init__(self):
        super().__init__("Central")

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x - h)) / (2 * h)


class RichardsonExtrapolation(DifferenceMethod):
    def __init__(self):
        super().__init__("Richardson")
        self.central = CentralDifference()

    def derivative(self, f, x, h):
        d_h = self.central.derivative(f, x, h)
        d_h2 = self.central.derivative(f, x, h / 2)
        return (4 * d_h2 - d_h) / 3
