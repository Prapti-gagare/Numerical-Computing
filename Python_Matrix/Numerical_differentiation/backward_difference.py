class BackwardDifference:
    def __init__(self):
        self.name = "Backward"

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        return (f.evaluate(x) - f.evaluate(x - h)) / h