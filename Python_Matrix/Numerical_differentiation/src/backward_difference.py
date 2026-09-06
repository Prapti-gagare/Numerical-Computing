from src.base import DividedDifference


class BackwardDifference(DividedDifference):
    def __init__(self):
        super().__init__("Backward")

    def derivative(self, f, x, h):
        return (f.evaluate(x) - f.evaluate(x - h)) / h
