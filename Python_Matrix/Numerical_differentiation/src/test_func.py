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
