class TestFunction:
    def __init__(self, name, function, exact_derivative=None, antiderivative=None):
        self.name = name
        self.function = function
        self.exact_derivative = exact_derivative
        self.antiderivative = antiderivative

    def get_name(self):
        return self.name

    def evaluate(self, x):
        return self.function(x)

    def exact(self, x):
        return self.exact_derivative(x)

    def exact_integral(self, a, b):
        return self.antiderivative(b) - self.antiderivative(a)
