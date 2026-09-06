from src.base import DividedDifference
from src.central_difference import CentralDifference


class RichardsonExtrapolation(DividedDifference):
    def __init__(self):
        super().__init__("Richardson")
        self.central = CentralDifference()

    def derivative(self, f, x, h):
        d_h = self.central.derivative(f, x, h)
        d_h2 = self.central.derivative(f, x, h / 2)

        return (4 * d_h2 - d_h) / 3
