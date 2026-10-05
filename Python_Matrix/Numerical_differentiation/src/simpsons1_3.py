from src.base import IntegrationMethod

class Simpson13Rule(IntegrationMethod):
    def __init__(self):
        super().__init__("Simpson's 1/3 Rule")

    def step_size(self, a, b, n):
        return (b - a) / n

    def integrate(self, f, a, b, n):
        if n < 2 or n % 2 != 0:
            raise ValueError("Number of subintervals n must be even and >= 2")

        h = self.step_size(a, b, n)
        total = f.evaluate(a) + f.evaluate(b)

        for i in range(1, n):
            x = a + i * h
            value = f.evaluate(x)
            if i % 2 == 0:
                total += 2 * value
            else:
                total += 4 * value

        return (h / 3) * total
