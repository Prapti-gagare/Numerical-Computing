from central_difference import CentralDifference


class RichardsonExtrapolation:
    def __init__(self):
        self.name = "Richardson"
        self.central = CentralDifference()

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        d_h = self.central.derivative(f, x, h)
        d_h2 = self.central.derivative(f, x, h / 2)

        return (4 * d_h2 - d_h) / 3