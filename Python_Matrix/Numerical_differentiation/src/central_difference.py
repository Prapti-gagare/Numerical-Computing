class CentralDifference:
    def __init__(self):
        self.name = "Central"

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x - h)) / (2 * h)