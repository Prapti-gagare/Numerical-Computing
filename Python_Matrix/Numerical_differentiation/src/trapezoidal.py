from src.base import IntegrationMethod


class TrapezoidalRule(IntegrationMethod):
    def __init__(self):
        super().__init__("Trapezoidal")

    def step_size(self, a, b, n):
        return (b - a) / n

    def integrate(self, f, a, b, n):
        if n < 1:
            raise ValueError("Number of trapezoids n must be >= 1")

        h = self.step_size(a, b, n)

        # I ~ h * [ f(a)/2 + f(x_1) + ... + f(x_{n-1}) + f(b)/2 ]
        total = 0.5 * (f.evaluate(a) + f.evaluate(b))
        for i in range(1, n):
            total += f.evaluate(a + i * h)

        return h * total
