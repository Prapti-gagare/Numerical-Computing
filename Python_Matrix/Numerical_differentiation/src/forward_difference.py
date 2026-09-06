from src.base import DividedDifference


class ForwardDifference(DividedDifference):
    def __init__(self):
        super().__init__("Forward")

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x)) / h
