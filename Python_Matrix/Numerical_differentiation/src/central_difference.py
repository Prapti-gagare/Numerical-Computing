from src.base import DividedDifference


class CentralDifference(DividedDifference):
    def __init__(self):
        super().__init__("Central")

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x - h)) / (2 * h)
