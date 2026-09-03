class ForwardDifference:
    def __init__(self):
        self.name = "Forward"

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        return (f.evaluate(x + h) - f.evaluate(x)) / h